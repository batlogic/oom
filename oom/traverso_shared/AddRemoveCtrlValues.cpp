//=========================================================
//  OOMidi
//  OpenOctave Midi and Audio Editor
//
//    add ctrl value command class
//
//  (C) Copyright 2011 Remon Sijrier
//=========================================================


#include "AddRemoveCtrlValues.h"

#include "ctrl.h"

AddRemoveCtrlValues::AddRemoveCtrlValues(CtrlList *cl, QList<CtrlVal> ctrlValues, int type)
	: OOMCommand(tr("Add Nodes"))
	, m_cl(cl)
	, m_ctrlValues(ctrlValues)
	, m_type(type)
{
	m_startValue = m_cl->value(0);
}

AddRemoveCtrlValues::AddRemoveCtrlValues(CtrlList *cl, CtrlVal ctrlValue, int type)
	: OOMCommand(tr("Add Node"))
	, m_cl(cl)
	, m_type(type)
{
	m_ctrlValues << ctrlValue;
	m_startValue = m_cl->value(0);
}

int AddRemoveCtrlValues::do_action()
{
	if (m_type == ADD)
	{
		foreach(CtrlVal v, m_ctrlValues)
		{
			m_cl->add(v.getFrame(), v.val);
		}
	}
	else
	{
		foreach(CtrlVal v, m_ctrlValues) {
			m_cl->del(v.getFrame());
		}
		m_cl->add(0, m_startValue);
	}


	return 1;
}

int AddRemoveCtrlValues::undo_action()
{
	if (m_type == ADD)
	{
		foreach(CtrlVal v, m_ctrlValues)
		{
			m_cl->del(v.getFrame());
		}
		m_cl->add(0, m_startValue);
	}
	else
	{
		foreach(CtrlVal v, m_ctrlValues)
		{
			m_cl->add(v.getFrame(), v.val);
		}
	}

	return 1;
}
