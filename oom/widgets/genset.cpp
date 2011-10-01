//=========================================================
//  OOMidi
//  OpenOctave Midi and Audio Editor
//  $Id: genset.cpp,v 1.7.2.8 2009/12/01 03:52:40 terminator356 Exp $
//
//  (C) Copyright 2001-2004 Werner Schweer (ws@seh.de)
//=========================================================

#include <stdio.h>

#include <QFileDialog>
#include <QRect>
#include <QShowEvent>

#include "genset.h"
#include "app.h"
#include "gconfig.h"
#include "midiseq.h"
#include "globals.h"
#include "icons.h"

static int rtcResolutions[] = {
	1024, 2048, 4096, 8192, 16384, 32768
};
static int divisions[] = {
	48, 96, 192, 384, 768, 1536, 3072, 6144, 12288
};
static int dummyAudioBufSizes[] = {
	16, 32, 64, 128, 256, 512, 1024, 2048
};

//---------------------------------------------------------
//   GlobalSettingsConfig
//---------------------------------------------------------

GlobalSettingsConfig::GlobalSettingsConfig(QWidget* parent)
: QDialog(parent)
{
	setupUi(this);
	groupBox13->hide();
	vstInPlaceTextLabel->hide();
	vstInPlaceCheckBox->hide();
	startUpBox->hide();
	startSongGroup = new QButtonGroup(this);
	startSongGroup->addButton(startLastButton, 0);
	startSongGroup->addButton(startEmptyButton, 1);
	startSongGroup->addButton(startSongButton, 2);
	for (unsigned i = 0; i < sizeof (rtcResolutions) / sizeof (*rtcResolutions); ++i)
	{
		if (rtcResolutions[i] == config.rtcTicks)
		{
			rtcResolutionSelect->setCurrentIndex(i);
			break;
		}
	}
	for (unsigned i = 0; i < sizeof (divisions) / sizeof (*divisions); ++i)
	{
		if (divisions[i] == config.division)
		{
			midiDivisionSelect->setCurrentIndex(i);
			break;
		}
	}
	for (unsigned i = 0; i < sizeof (divisions) / sizeof (*divisions); ++i)
	{
		if (divisions[i] == config.guiDivision)
		{
			guiDivisionSelect->setCurrentIndex(i);
			break;
		}
	}
	for (unsigned i = 0; i < sizeof (dummyAudioBufSizes) / sizeof (*dummyAudioBufSizes); ++i)
	{
		if (dummyAudioBufSizes[i] == config.dummyAudioBufSize)
		{
			dummyAudioSize->setCurrentIndex(i);
			break;
		}
	}

	userInstrumentsPath->setText(config.userInstrumentsDir);
	selectInstrumentsDirButton->setIcon(*openIcon);
	defaultInstrumentsDirButton->setIcon(*undoIcon);
	connect(selectInstrumentsDirButton, SIGNAL(clicked()), SLOT(selectInstrumentsPath()));
	connect(defaultInstrumentsDirButton, SIGNAL(clicked()), SLOT(defaultInstrumentsPath()));

	guiRefreshSelect->setValue(config.guiRefresh);
	minSliderSelect->setValue(int(config.minSlider));
	minMeterSelect->setValue(config.minMeter);
	freewheelCheckBox->setChecked(config.freewheelMode);
	denormalCheckBox->setChecked(config.useDenormalBias);
	outputLimiterCheckBox->setChecked(config.useOutputLimiter);
	vstInPlaceCheckBox->setChecked(config.vstInPlace);
	dummyAudioRate->setValue(config.dummyAudioSampleRate);

	//DummyAudioDevice* dad = dynamic_cast<DummyAudioDevice*>(audioDevice);
	//dummyAudioRealRate->setText(dad ? QString().setNum(sampleRate) : "---");
	dummyAudioRealRate->setText(QString().setNum(sampleRate));

	startSongEntry->setText(config.startSong);
	startSongGroup->button(config.startMode)->setChecked(true);

	//showTransport->setChecked(config.transportVisible);
	//showBigtime->setChecked(config.bigTimeVisible);
	//showMixer->setChecked(config.mixer1Visible);
	//showMixer2->setChecked(config.mixer2Visible);

	/*composerX->setValue(config.geometryMain.x());
	composerY->setValue(config.geometryMain.y());
	composerW->setValue(config.geometryMain.width());
	composerH->setValue(config.geometryMain.height());

	transportX->setValue(config.geometryTransport.x());
	transportY->setValue(config.geometryTransport.y());

	bigtimeX->setValue(config.geometryBigTime.x());
	bigtimeY->setValue(config.geometryBigTime.y());
	bigtimeW->setValue(config.geometryBigTime.width());
	bigtimeH->setValue(config.geometryBigTime.height());*/

	//mixerX->setValue(config.geometryMixer.x());
	//mixerY->setValue(config.geometryMixer.y());
	//mixerW->setValue(config.geometryMixer.width());
	//mixerH->setValue(config.geometryMixer.height());
	/*mixerX->setValue(config.mixer1.geometry.x());
	mixerY->setValue(config.mixer1.geometry.y());
	mixerW->setValue(config.mixer1.geometry.width());
	mixerH->setValue(config.mixer1.geometry.height());
	mixer2X->setValue(config.mixer2.geometry.x());
	mixer2Y->setValue(config.mixer2.geometry.y());
	mixer2W->setValue(config.mixer2.geometry.width());
	mixer2H->setValue(config.mixer2.geometry.height());*/

	//setMixerCurrent->setEnabled(oom->mixer1Window());
	//setMixer2Current->setEnabled(oom->mixer2Window());

	//setBigtimeCurrent->setEnabled(oom->bigtimeWindow());
	//setTransportCurrent->setEnabled(oom->transportWindow());

	showSplash->setChecked(config.showSplashScreen);
	showDidYouKnow->setChecked(config.showDidYouKnow);
	externalWavEditorSelect->setText(config.externalWavEditor);
	oldStyleStopCheckBox->setChecked(config.useOldStyleStopShortCut);
	moveArmedCheckBox->setChecked(config.moveArmedCheckBox);
	projectSaveCheckBox->setChecked(config.useProjectSaveDialog);
	
	m_chkAutofade->setChecked(config.useAutoCrossFades);

	//updateSettings();    // TESTING

	connect(applyButton, SIGNAL(clicked()), SLOT(apply()));
	connect(okButton, SIGNAL(clicked()), SLOT(ok()));
	connect(cancelButton, SIGNAL(clicked()), SLOT(cancel()));
	//connect(setMixerCurrent, SIGNAL(clicked()), SLOT(mixerCurrent()));
	//connect(setMixer2Current, SIGNAL(clicked()), SLOT(mixer2Current()));
	//connect(setBigtimeCurrent, SIGNAL(clicked()), SLOT(bigtimeCurrent()));
	//connect(setComposerCurrent, SIGNAL(clicked()), SLOT(composerCurrent()));
	//connect(setTransportCurrent, SIGNAL(clicked()), SLOT(transportCurrent()));
}

//---------------------------------------------------------
//   updateSettings
//---------------------------------------------------------

void GlobalSettingsConfig::updateSettings()
{
	for (unsigned i = 0; i < sizeof (rtcResolutions) / sizeof (*rtcResolutions); ++i)
	{
		if (rtcResolutions[i] == config.rtcTicks)
		{
			rtcResolutionSelect->setCurrentIndex(i);
			break;
		}
	}
	for (unsigned i = 0; i < sizeof (divisions) / sizeof (*divisions); ++i)
	{
		if (divisions[i] == config.division)
		{
			midiDivisionSelect->setCurrentIndex(i);
			break;
		}
	}
	for (unsigned i = 0; i < sizeof (divisions) / sizeof (*divisions); ++i)
	{
		if (divisions[i] == config.guiDivision)
		{
			guiDivisionSelect->setCurrentIndex(i);
			break;
		}
	}
	for (unsigned i = 0; i < sizeof (dummyAudioBufSizes) / sizeof (*dummyAudioBufSizes); ++i)
	{
		if (dummyAudioBufSizes[i] == config.dummyAudioBufSize)
		{
			dummyAudioSize->setCurrentIndex(i);
			break;
		}
	}

	guiRefreshSelect->setValue(config.guiRefresh);
	minSliderSelect->setValue(int(config.minSlider));
	minMeterSelect->setValue(config.minMeter);
	freewheelCheckBox->setChecked(config.freewheelMode);
	denormalCheckBox->setChecked(config.useDenormalBias);
	outputLimiterCheckBox->setChecked(config.useOutputLimiter);
	vstInPlaceCheckBox->setChecked(config.vstInPlace);
	dummyAudioRate->setValue(config.dummyAudioSampleRate);

	//DummyAudioDevice* dad = dynamic_cast<DummyAudioDevice*>(audioDevice);
	//dummyAudioRealRate->setText(dad ? QString().setNum(sampleRate) : "---");
	dummyAudioRealRate->setText(QString().setNum(sampleRate));

	startSongEntry->setText(config.startSong);
	startSongGroup->button(config.startMode)->setChecked(true);

	//showTransport->setChecked(config.transportVisible);
	//showBigtime->setChecked(config.bigTimeVisible);
	//showMixer->setChecked(config.mixer1Visible);
	//showMixer2->setChecked(config.mixer2Visible);

	/*composerX->setValue(config.geometryMain.x());
	composerY->setValue(config.geometryMain.y());
	composerW->setValue(config.geometryMain.width());
	composerH->setValue(config.geometryMain.height());

	transportX->setValue(config.geometryTransport.x());
	transportY->setValue(config.geometryTransport.y());

	bigtimeX->setValue(config.geometryBigTime.x());
	bigtimeY->setValue(config.geometryBigTime.y());
	bigtimeW->setValue(config.geometryBigTime.width());
	bigtimeH->setValue(config.geometryBigTime.height());*/

	//mixerX->setValue(config.geometryMixer.x());
	//mixerY->setValue(config.geometryMixer.y());
	//mixerW->setValue(config.geometryMixer.width());
	//mixerH->setValue(config.geometryMixer.height());
	/*mixerX->setValue(config.mixer1.geometry.x());
	mixerY->setValue(config.mixer1.geometry.y());
	mixerW->setValue(config.mixer1.geometry.width());
	mixerH->setValue(config.mixer1.geometry.height());
	mixer2X->setValue(config.mixer2.geometry.x());
	mixer2Y->setValue(config.mixer2.geometry.y());
	mixer2W->setValue(config.mixer2.geometry.width());
	mixer2H->setValue(config.mixer2.geometry.height());*/

	//setMixerCurrent->setEnabled(oom->mixerWindow());
	//setMixerCurrent->setEnabled(oom->mixer1Window());
	//setMixer2Current->setEnabled(oom->mixer2Window());

	//setBigtimeCurrent->setEnabled(oom->bigtimeWindow());
	//setTransportCurrent->setEnabled(oom->transportWindow());

	showSplash->setChecked(config.showSplashScreen);
	showDidYouKnow->setChecked(config.showDidYouKnow);
	externalWavEditorSelect->setText(config.externalWavEditor);
	oldStyleStopCheckBox->setChecked(config.useOldStyleStopShortCut);
	moveArmedCheckBox->setChecked(config.moveArmedCheckBox);
	projectSaveCheckBox->setChecked(config.useProjectSaveDialog);
}

//---------------------------------------------------------
//   showEvent
//---------------------------------------------------------

void GlobalSettingsConfig::showEvent(QShowEvent* e)
{
	QDialog::showEvent(e);
	//updateSettings();     // TESTING
}

//---------------------------------------------------------
//   apply
//---------------------------------------------------------

void GlobalSettingsConfig::apply()
{
	int rtcticks = rtcResolutionSelect->currentIndex();
	config.guiRefresh = guiRefreshSelect->value();
	config.minSlider = minSliderSelect->value();
	config.minMeter = minMeterSelect->value();
	config.freewheelMode = freewheelCheckBox->isChecked();
	config.useDenormalBias = denormalCheckBox->isChecked();
	config.useOutputLimiter = outputLimiterCheckBox->isChecked();
	config.vstInPlace = vstInPlaceCheckBox->isChecked();
	config.rtcTicks = rtcResolutions[rtcticks];
	config.userInstrumentsDir = userInstrumentsPath->text();
	config.startSong = startSongEntry->text();
	config.startMode = startSongGroup->checkedId();
	int das = dummyAudioSize->currentIndex();
	config.dummyAudioBufSize = dummyAudioBufSizes[das];
	config.dummyAudioSampleRate = dummyAudioRate->value();

	int div = midiDivisionSelect->currentIndex();
	config.division = divisions[div];
	div = guiDivisionSelect->currentIndex();
	config.guiDivision = divisions[div];

	//config.transportVisible = showTransport->isChecked();
	//config.bigTimeVisible = showBigtime->isChecked();
	//config.mixer1Visible = showMixer->isChecked();
	//config.mixer2Visible = showMixer2->isChecked();

	//config.geometryMain.setX(composerX->value());
	//config.geometryMain.setY(composerY->value());
	//config.geometryMain.setWidth(composerW->value());
	//config.geometryMain.setHeight(composerH->value());

	//config.geometryTransport.setX(transportX->value());
	//config.geometryTransport.setY(transportY->value());
	//config.geometryTransport.setWidth(0);
	//config.geometryTransport.setHeight(0);

	//config.geometryBigTime.setX(bigtimeX->value());
	//config.geometryBigTime.setY(bigtimeY->value());
	//config.geometryBigTime.setWidth(bigtimeW->value());
	//config.geometryBigTime.setHeight(bigtimeH->value());

	//config.geometryMixer.setX(mixerX->value());
	//config.geometryMixer.setY(mixerY->value());
	//config.geometryMixer.setWidth(mixerW->value());
	//config.geometryMixer.setHeight(mixerH->value());
	//config.mixer1.geometry.setX(mixerX->value());
	//config.mixer1.geometry.setY(mixerY->value());
	//config.mixer1.geometry.setWidth(mixerW->value());
	//config.mixer1.geometry.setHeight(mixerH->value());
	//config.mixer2.geometry.setX(mixer2X->value());
	//config.mixer2.geometry.setY(mixer2Y->value());
	//config.mixer2.geometry.setWidth(mixer2W->value());
	//config.mixer2.geometry.setHeight(mixer2H->value());

	config.showSplashScreen = showSplash->isChecked();
	config.showDidYouKnow = showDidYouKnow->isChecked();
	config.externalWavEditor = externalWavEditorSelect->text();
	config.useOldStyleStopShortCut = oldStyleStopCheckBox->isChecked();
	config.moveArmedCheckBox = moveArmedCheckBox->isChecked();
	config.useProjectSaveDialog = projectSaveCheckBox->isChecked();
	config.useAutoCrossFades = m_chkAutofade->isChecked();
	//oom->showMixer1(config.mixer1Visible);
	//oom->showMixer2(config.mixer2Visible);

	//oom->showBigtime(config.bigTimeVisible);
	//oom->showTransport(config.transportVisible);
	/*QWidget* w = oom->transportWindow();
	if (w)
	{
		w->resize(config.geometryTransport.size());
		w->move(config.geometryTransport.topLeft());
	}
	//w = oom->mixerWindow();
	//if (w) {
	//      w->resize(config.geometryMixer.size());
	//      w->move(config.geometryMixer.topLeft());
	//      }
	w = oom->mixer1Window();
	if (w)
	{
		w->resize(config.mixer1.geometry.size());
		w->move(config.mixer1.geometry.topLeft());
	}
	w = oom->mixer2Window();
	if (w)
	{
		w->resize(config.mixer2.geometry.size());
		w->move(config.mixer2.geometry.topLeft());
	}
	w = oom->bigtimeWindow();
	if (w)
	{
		w->resize(config.geometryBigTime.size());
		w->move(config.geometryBigTime.topLeft());
	}*/
	//oom->resize(config.geometryMain.size());
	//oom->move(config.geometryMain.topLeft());

	oomUserInstruments = config.userInstrumentsDir;

	oom->setHeartBeat(); // set guiRefresh
	midiSeq->msgSetRtc(); // set midi tick rate
	oom->changeConfig(true); // save settings
}

//---------------------------------------------------------
//   ok
//---------------------------------------------------------

void GlobalSettingsConfig::ok()
{
	apply();
	close();
}

//---------------------------------------------------------
//   cancel
//---------------------------------------------------------

void GlobalSettingsConfig::cancel()
{
	close();
}

//---------------------------------------------------------
//   mixerCurrent
//---------------------------------------------------------
/*
void GlobalSettingsConfig::mixerCurrent()
{
	QWidget* w = oom->mixer1Window();
	if (!w)
		return;
	QRect r(w->frameGeometry());
	mixerX->setValue(r.x());
	mixerY->setValue(r.y());
	mixerW->setValue(r.width());
	mixerH->setValue(r.height());
}

//---------------------------------------------------------
//   mixer2Current
//---------------------------------------------------------

void GlobalSettingsConfig::mixer2Current()
{
	QWidget* w = oom->mixer2Window();
	if (!w)
		return;
	QRect r(w->frameGeometry());
	mixer2X->setValue(r.x());
	mixer2Y->setValue(r.y());
	mixer2W->setValue(r.width());
	mixer2H->setValue(r.height());
}

//---------------------------------------------------------
//   bigtimeCurrent
//---------------------------------------------------------

void GlobalSettingsConfig::bigtimeCurrent()
{
	QWidget* w = oom->bigtimeWindow();
	if (!w)
		return;
	QRect r(w->frameGeometry());
	bigtimeX->setValue(r.x());
	bigtimeY->setValue(r.y());
	bigtimeW->setValue(r.width());
	bigtimeH->setValue(r.height());
}

//---------------------------------------------------------
//   composerCurrent
//---------------------------------------------------------

void GlobalSettingsConfig::composerCurrent()
{
	QRect r(oom->frameGeometry());
	composerX->setValue(r.x());
	composerY->setValue(r.y());
	composerW->setValue(r.width());
	composerH->setValue(r.height());
}

//---------------------------------------------------------
//   transportCurrent
//---------------------------------------------------------

void GlobalSettingsConfig::transportCurrent()
{
	QWidget* w = oom->transportWindow();
	if (!w)
		return;
	QRect r(w->frameGeometry());
	transportX->setValue(r.x());
	transportY->setValue(r.y());
}
*/
void GlobalSettingsConfig::selectInstrumentsPath()
{
	QString dir = QFileDialog::getExistingDirectory(this,
			tr("Selects instruments directory"),
			config.userInstrumentsDir);
	userInstrumentsPath->setText(dir);
}

void GlobalSettingsConfig::defaultInstrumentsPath()
{
	QString dir = configPath + "/instruments";
	userInstrumentsPath->setText(dir);
}
