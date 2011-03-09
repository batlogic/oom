//=========================================================
//  OOMidi
//  OpenOctave Midi and Audio Editor
//    $Id: piano.cpp,v 1.3 2004/05/31 11:48:55 lunar_shuttle Exp $
//  (C) Copyright 1999 Werner Schweer (ws@seh.de)
//=========================================================

#include <QMouseEvent>
#include <QPainter>

#include <stdio.h>

#include "piano.h"

//{{{
static const char *mk1_xpmC1[] = {
      "40 10 3 1",
      ". c #dedede",
      "# c #292929",
      "@ c none",
      "@@@@@@@@@@@@@@@@@@@@@@@................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",     // 10
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };
static const char *mk1_xpmC2[] = {
      "40 10 3 1",
      ". c #dedede",
      "# c #292929",
      "@ c none",
      "@@@@@@@@@@@@@@@@@@@@@@@................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",     // 10
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };
static const char *mk1_xpmC3[] = {
      "40 10 3 1",
      ". c #dedede",
      "# c #292929",
      "@ c none",
      "@@@@@@@@@@@@@@@@@@@@@@@................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",     // 10
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };
static const char *mk1_xpmC4[] = {
      "40 10 3 1",
      ". c #dedede",
      "# c #292929",
      "@ c none",
      "@@@@@@@@@@@@@@@@@@@@@@@................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",     // 10
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };
static const char *mk1_xpmC5[] = {
      "40 10 3 1",
      ". c #dedede",
      "# c #292929",
      "@ c none",
      "@@@@@@@@@@@@@@@@@@@@@@@................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",     // 10
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };

static const char *mk1_xpmC6[] = {
      "40 10 3 1",
      ". c #dedede",
      "# c #292929",
      "@ c none",
      "@@@@@@@@@@@@@@@@@@@@@@@................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",     // 10
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };

static const char *mk1_xpmC7[] = {
      "40 10 3 1",
      ". c #dedede",
      "# c #292929",
      "@ c none",
      "@@@@@@@@@@@@@@@@@@@@@@@................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",     // 10
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };
static const char *mk1_xpmC8[] = {
      "40 10 3 1",
      ". c #dedede",//white keys
      "# c #292929",//black keys
      "@ c none",
      "@@@@@@@@@@@@@@@@@@@@@@@................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",     // 10
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };
//}}}	  
//{{{
static const char *mk1_xpm[] = {/*{{{*/
      "40 13 2 1",
      //". c #2d95b7",//highlight
      ". c #92c165",//highlight
      "# c none",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      "#######################................#",
      "########################...............#",
      "########################...............#",
      "####################################### ",
      };/*}}}*/

static const char *mk2_xpm[] = {/*{{{*/
      "40 13 2 1",
      //". c #2d95b7",
      ". c #92c165",//highlight
      "# c none",
      "########################...............#",
      "########################...............#",
      "#######################................#", //------------------------
      ".......................................#",
      ".......................................#",
      ".......................................#",     // 6
      ".......................................#",
      ".......................................#",
      ".......................................#", //--------------------------
      "#######################................#",
      "########################...............#",
      "########################...............#",     // 7
      "####################################### ",
      };/*}}}*/

static const char *mk3_xpm[] = {
      "40 13 2 1",
      //". c #2d95b7",
      ". c #92c165",//highlight
      "# c none",
      "########################...............#",
      "########################...............#",
      "#######################................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      "########################################",
      };

static const char *mk4_xpm[] = {
      "40 13 3 1",
      //"# c #2d95b7",
      "# c #92c165",//highlight
      ". c none",
      "$ c #2d95b7",
      "........................................",
      "........................................",
      "........................................",
      "$$$$$$$$$$$$$$$$$$$$$$$.................",
      "#######################$................",
      "#######################$................",
      "#######################$................",
      "#######################$................",
      "#######################$................",
      "$$$$$$$$$$$$$$$$$$$$$$$.................",
      "........................................",
      "........................................",
      "........................................",
      };
//}}}	  
//{{{
static const char *mk1_xpm_lowlight[] = {
      "40 13 3 1",
      //". c #7b7b7b",//highlight
      //". c #c1c1c1",
      ". c #fffce6",
      "# c none",
      "$ c #fffce6",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      "#######################................$",
      "########################...............$",
      "########################...............$",
      "########################$$$$$$$$$$$$$$$ ",
      };

static const char *mk2_xpm_lowlight[] = {
      "40 13 3 1",
      //". c #7b7b7b",
      ". c #fffce6",
      "# c none",
      "$ c #fffce6",
      "########################...............$",
      "########################...............$",
      "#######################................$", //------------------------
      ".......................................$",
      ".......................................$",
      ".......................................$",     // 6
      ".......................................$",
      ".......................................$",
      ".......................................$", //--------------------------
      "#######################................$",
      "########################...............$",
      "########################...............$",     // 7
      "########################$$$$$$$$$$$$$$$ ",
      };

static const char *mk3_xpm_lowlight[] = {
      "40 13 3 1",
      ". c #fffce6",
      "# c none",
      "$ c #fffce6",
      "########################...............$",
      "########################...............$",
      "#######################................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",
      };

static const char *mk4_xpm_lowlight[] = {
      "40 13 2 1",
      //"# c #2c2c2c",
      "# c #fffce6",
      ". c none",
      "........................................",
      "........................................",
      "........................................",
      "#######################.................",
      "########################................",
      "########################................",
      "########################................",
      "########################................",
      "########################................",
      "#######################.................",
      "........................................",
      "........................................",
      "........................................",
      };
//}}}	  
//{{{
static const char *mk1_xpm_normal[] = {/*{{{*/
      "40 13 2 1",
      //". c #dedede",
      //". c #a0cfe1",
      ". c #aecad4",
      //"# c #292929",
      //"# c #06384b",
      "# c #14323e",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      "#######################................#",
      "########################...............#",
      "########################...............#",
      "####################################### ",
      };/*}}}*/

static const char *mk2_xpm_normal[] = {
      "40 13 2 1",
      //". c #dedede",
      //". c #a0cfe1",
      ". c #aecad4",
      //"# c #292929",
      //"# c #06384b",
      "# c #14323e",
      "########################...............#",
      "########################...............#",
      "#######################................#", //------------------------
      ".......................................#",
      ".......................................#",
      ".......................................#",     // 6
      ".......................................#",
      ".......................................#",
      ".......................................#", //--------------------------
      "#######################................#",
      "########################...............#",
      "########################...............#",     // 7
      "####################################### ",
      };

static const char *mk3_xpm_normal[] = {
      "40 13 2 1",
      //". c #dedede",
      //". c #a0cfe1",
      ". c #aecad4",
      //"# c #292929",
      //"# c #08455c",
      //"# c #06384b",
      "# c #14323e",
      "########################...............#",
      "########################...............#",
      "#######################................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      "########################################",
      };

static const char *mk4_xpm_normal[] = {
      "40 13 2 1",
      //". c #dedede",
	  ". c none",
      //"# c #292929",
      //"# c #08455c",
      //"# c #06384b",
      "# c #14323e",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      "#######################................#",
      "########################...............#",
      "########################...............#",
      "########################...............#",
      "########################...............#",
      "########################...............#",
      "#######################................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };
static const char *mk5_xpm_normal[] = {
      "40 13 3 1",
      "$ c #7b7b7b",
      //". c #dedede",
      //". c #a0cfe1",
      ". c #aecad4",
      //"# c #292929",
      //"# c #08455c",
      //"# c #06384b",
      "# c #14323e",
      "########################...............#",
      "########################...............#",
      "#######################................#", //------------------------
      ".......................................#",
      ".......................................#",
      ".......................................#",     // 6
      ".......................................#",
      ".......................................#",
      ".......................................#", //--------------------------
      "$$$$$$$$$$$$$$$$$$$$$$$................#",
      "$$$$$$$$$$$$$$$$$$$$$$$$...............#",
      "$$$$$$$$$$$$$$$$$$$$$$$$...............#",     // 7
      "$$$$$$$$$$$$$$$$$$$$$$$$############### ",
      };
static const char *mk6_xpm_normal[] = {/*{{{*/
      "40 13 3 1",
      //". c #dedede",
      //". c #a0cfe1",
      ". c #aecad4",
      //"# c #292929",
      //"# c #08455c",
      //"# c #06384b",
      "# c #14323e",
      "$ c #7b7b7b",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      "$$$$$$$$$$$$$$$$$$$$$$$................#",
      "$$$$$$$$$$$$$$$$$$$$$$$$...............#",
      "$$$$$$$$$$$$$$$$$$$$$$$$...............#",
      "$$$$$$$$$$$$$$$$$$$$$$$$############### ",
      };/*}}}*/
//}}}	  
//{{{
static const char *mk1_xpm_switch[] = {
      "40 13 3 1",
      //". c #7b7b7b",//highlight
      ". c #c87171",
      "# c none",
      "$ c #292929",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      "#######################................$",
      "########################...............$",
      "########################...............$",
      "########################$$$$$$$$$$$$$$$ ",
      };

static const char *mk2_xpm_switch[] = {
      "40 13 3 1",
      //". c #7b7b7b",
      ". c #c87171",
      "# c none",
      "$ c #292929",
      "########################...............$",
      "########################...............$",
      "#######################................$", //------------------------
      ".......................................$",
      ".......................................$",
      ".......................................$",     // 6
      ".......................................$",
      ".......................................$",
      ".......................................$", //--------------------------
      "#######################................$",
      "########################...............$",
      "########################...............$",     // 7
      "########################$$$$$$$$$$$$$$$ ",
      };

static const char *mk3_xpm_switch[] = {
      "40 13 3 1",
      ". c #c87171",
      "# c none",
      "$ c #292929",
      "########################...............$",
      "########################...............$",
      "#######################................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      ".......................................$",
      "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",
      };

static const char *mk4_xpm_switch[] = {
      "40 13 2 1",
      //"# c #2c2c2c",
      "# c #770000",
      ". c none",
      "........................................",
      "........................................",
      "........................................",
      "#######################.................",
      "########################................",
      "########################................",
      "########################................",
      "########################................",
      "########################................",
      "#######################.................",
      "........................................",
      "........................................",
      "........................................",
      };
static const char *mk5_xpm_switch[] = {/*{{{*/
      "40 13 4 1",
      "$ c #7b7b7b",
      ". c #dedede",
      "# c #770000",
      "d c #292929",
      "########################...............d",
      "########################...............d",
      "#######################................d", //------------------------
      ".......................................d",
      ".......................................d",
      ".......................................d",     // 6
      ".......................................d",
      ".......................................d",
      ".......................................d", //--------------------------
      "$$$$$$$$$$$$$$$$$$$$$$$................d",
      "$$$$$$$$$$$$$$$$$$$$$$$$...............d",
      "$$$$$$$$$$$$$$$$$$$$$$$$...............d",     // 7
      "$$$$$$$$$$$$$$$$$$$$$$$$ddddddddddddddd ",
      };/*}}}*/
static const char *mk6_xpm_switch[] = {/*{{{*/
      "40 13 4 1",
      "$ c #7b7b7b",
      ". c #c87171",
      "# c #770000",
      "d c #292929",
      "########################...............d",
      "########################...............d",
      "#######################................d", //------------------------
      ".......................................d",
      ".......................................d",
      ".......................................d",     // 6
      ".......................................d",
      ".......................................d",
      ".......................................d", //--------------------------
      "$$$$$$$$$$$$$$$$$$$$$$$................d",
      "$$$$$$$$$$$$$$$$$$$$$$$$...............d",
      "$$$$$$$$$$$$$$$$$$$$$$$$...............d",     // 7
      "$$$$$$$$$$$$$$$$$$$$$$$$ddddddddddddddd ",
      };/*}}}*/
//}}}	  
/*
      0   1   2  3  4  5  6  7  8  9  10
      c-2 c-1 C0 C1 C2 C3 C4 C5 C6 C7 C8 - G8

      Grid �ber Oktave:

           +------------+ ------------------------------
       11  |            |
           |         h  |         7
           +------+     |
       10  |  a#  +-----+ ..............................
           +------+  a  |
        9  |            |         6
           +------+     |
        8  |  g#  +-----+ ..............................
           +------+  g  |
        7  |            |         5
           +------+     |
        6  |  f#  +-----+ ..............................
           +------+  f  |
        5  |            |         4
           |            |
           +------------+ ------------------------------
        4  |            |
           |         e  |         3
           +------+     |
        3  |  d#  +-----+ ..............................
           +------+  d  |
        2  |            |         2
           +------+     |
        1  |  c#  +-----+ ..............................
           +------+  c  |
           |            |         1
        0  |            |
           +------------+ ------------------------------
 */

//---------------------------------------------------------
//   Piano
//---------------------------------------------------------

Piano::Piano(QWidget* parent, int ymag)
   : View(parent, 1, ymag)
      {
      setMouseTracking(true);
      curPitch = -1;
      c_keys[0] = new QPixmap(mk1_xpmC8);
      c_keys[1] = new QPixmap(mk1_xpmC7);
      c_keys[2] = new QPixmap(mk1_xpmC6);
      c_keys[3] = new QPixmap(mk1_xpmC5);
      c_keys[4] = new QPixmap(mk1_xpmC4);
      c_keys[5] = new QPixmap(mk1_xpmC3);
      c_keys[6] = new QPixmap(mk1_xpmC2);
      c_keys[7] = new QPixmap(mk1_xpmC1);
	  
	  //setup all the highlight colors 	
      mk1 = new QPixmap(mk1_xpm);
      mk2 = new QPixmap(mk2_xpm);
      mk3 = new QPixmap(mk3_xpm);
      mk4 = new QPixmap(mk4_xpm);
	  
	  //setup all the highlight colors 	
      mk1_l = new QPixmap(mk1_xpm_lowlight);
      mk2_l = new QPixmap(mk2_xpm_lowlight);
      mk3_l = new QPixmap(mk3_xpm_lowlight);
      mk4_l = new QPixmap(mk4_xpm_lowlight);
	  
	  //setup all the highlight colors 	
      mk1_n = new QPixmap(mk1_xpm_normal);
      mk2_n = new QPixmap(mk2_xpm_normal);
      mk3_n = new QPixmap(mk3_xpm_normal);
      mk4_n = new QPixmap(mk4_xpm_normal);
      mk5_n = new QPixmap(mk5_xpm_normal);
      mk6_n = new QPixmap(mk6_xpm_normal);
	  
	  //setup all the keyswitch colors 	
      mk1_s = new QPixmap(mk1_xpm_switch);
      mk2_s = new QPixmap(mk2_xpm_switch);
      mk3_s = new QPixmap(mk3_xpm_switch);
      mk4_s = new QPixmap(mk4_xpm_switch);
      mk5_s = new QPixmap(mk5_xpm_switch);
      mk6_s = new QPixmap(mk6_xpm_switch);

	  /*enabled = new QList<int>();
	  QStringList sls;
	  sls << "55" << "56" << "57" << "58" << "59" << "60" << "61" << "62" << "63" << "64" << "65" << "66" << "67" << "68" << "69" << "70" << "71" << "72" << "73" << "74" << "75" << "76" << "77" << "78" << "79" << "80" << "81" << "82" << "83" << "84" << "85" << "86" << "87" << "88" << "89" << "90" << "91" << "92" << "93" << "94" << "95" << "96" << "97" << "98" << "99";// << "100";      
	  //sls << "55" << "56" << "57" << "58" << "64" << "65" << "66" << "67" << "72" << "73" << "74" << "77" << "79" << "81" << "82" << "83" << "84" << "85" << "90" << "91" << "92" << "93" << "97" << "98";      
      QStringListIterator iter(sls);
	  while(iter.hasNext())
	  {
	  	enabled->append(iter.next().toInt());
	  }
	  
	  keyswitch = new QList<int>();
	  QStringList keyswitchlist;
	  keyswitchlist << "105" << "106" << "107" << "108" << "110" << "111" << "112" << "113";      
      QStringListIterator iterswitch(keyswitchlist);
	  while(iterswitch.hasNext())
	  {
	  	keyswitch->append(iterswitch.next().toInt());
	  }*/
	  keyDown = -1;
      button = Qt::NoButton;
      }

//---------------------------------------------------------
//   draw
//---------------------------------------------------------

void Piano::draw(QPainter& p, const QRect& r)
{
      QPoint offset(0, KH*2);
      //p.drawTiledPixmap(r, *octave, r.topLeft()+offset);

      // draw C notes
      /*for (int drawKey = 0; drawKey < 8;drawKey++) 
	  {
      		p.drawTiledPixmap(r, *octave, r.topLeft()+offset);
      		int octaveSize=91;

        	int drawY = octaveSize * drawKey + 81 - KH*2;
        	if (drawY > r.y() && drawY < r.y() + r.height()) 
			{
          		//printf("drawing c %d at %d r.y %d r.x %d\n",drawKey, drawY, r.y(), r.x());
          		p.drawPixmap(0,drawY,*c_keys[drawKey]);
        	}
      }*/

	  bool preOn = false;
	  for(int i = 0; i <= 127; ++i)
	  {
     	 switch(i % 12) /*{{{*/
	 	 {
     	       case 0:
     	       case 5:
     	             //pm2 = mk3_l;
					if(keyswitch.contains(i))
      					p.drawPixmap(0, pitch2y(i), *mk3_s);
					else if(enabled.isEmpty() || !enabled.contains(i))
      					p.drawPixmap(0, pitch2y(i), *mk3_l);
					else
      					p.drawPixmap(0, pitch2y(i), *mk3_n);
					preOn = false;
     	             break;
     	       case 2:
     	       case 7:
     	       case 9:
					if(keyswitch.contains(i))
					{
						if(preOn)
						{
							if(!enabled.isEmpty() && enabled.contains(i))
      							p.drawPixmap(0, pitch2y(i), *mk5_s);
							else
      							p.drawPixmap(0, pitch2y(i), *mk6_s);
						}
						else
      						p.drawPixmap(0, pitch2y(i), *mk2_s);
					}
					else if(enabled.isEmpty() || !enabled.contains(i))
					{
      					p.drawPixmap(0, pitch2y(i), *mk2_l);
					}
					else
					{
						if(preOn)
      						p.drawPixmap(0, pitch2y(i), *mk5_n);
						else
      						p.drawPixmap(0, pitch2y(i), *mk2_n);
					}
     	             break;
     	       case 4:
     	       case 11:
     	             //pm2 = mk1_l;
					if(keyswitch.contains(i))
      					p.drawPixmap(0, pitch2y(i), *mk1_s);
					else if(enabled.isEmpty() || !enabled.contains(i))
					{
      					p.drawPixmap(0, pitch2y(i), *mk1_l);
					}
					else
					{
						if(preOn)
      						p.drawPixmap(0, pitch2y(i), *mk6_n);
						else
      						p.drawPixmap(0, pitch2y(i), *mk1_n);
					}
					preOn = false;
     	             break;
            default:
					if(keyswitch.contains(i))
					{
      					p.drawPixmap(0, pitch2y(i), *mk4_s);
						preOn = false;
					}
					else if(enabled.isEmpty() || !enabled.contains(i))
					{
      					p.drawPixmap(0, pitch2y(i), *mk4_l);
						preOn = true;
					}
					else
					{
      					p.drawPixmap(0, pitch2y(i), *mk4_n);
						preOn = false;
					}
                  break;
     	 }/*}}}*/
	  }

      if (curPitch != -1)
	  {
	 	 int y = pitch2y(curPitch);
     	 QPixmap* pm = 0;
     	 switch(curPitch % 12) /*{{{*/
	 	 {
     	       case 0:
     	       case 5:
     	             pm = mk3;
     	             break;
     	       case 2:
     	       case 7:
     	       case 9:
     	             pm = mk2;
     	             break;
     	       case 4:
     	       case 11:
     	             pm = mk1;
     	             break;
     	       default:
     	             pm = mk4;
     	             break;
     	 }/*}}}*/
     	 p.drawPixmap(0, y, *pm);
	  }
      //QFont font;
      //font.setPixelSize(10);
      //p.setFontFamily("fixed-font");
      //p.setFont(font);
      p.setFont(QFont("fixed-font", 7));
      // draw C notes
      for (int drawKey = 0; drawKey < 8;drawKey++) 
	  {	
	      int octaveSize=91;
          int drawY = octaveSize * drawKey + 81 - KH*2;
          if (drawY > r.y() && drawY < r.y() + r.height()) 
		  {
          		p.drawText(23, drawY + 8, "C" + QString::number(8 - drawKey));
          }
      }
      
}

void Piano::setMIDIKeyBindings(QList<int> e, QList<int> s)
{
	enabled = e;//info->key_bindings;
	keyswitch = s;//info->keyswitch_bindings;
	redraw();
}

//---------------------------------------------------------
//   pitch2y
//---------------------------------------------------------

int Piano::pitch2y(int pitch) const
{
      int tt[] = 
	  {
            12, 19, 25, 32, 38, 51, 58, 64, 71, 77, 84, 90
      };
      int y = (75 * KH) - (tt[pitch%12] + (7 * KH) * (pitch/12));
      if (y < 0)
      	y = 0;
      return y;
}

//---------------------------------------------------------
//   y2pitch
//---------------------------------------------------------

int Piano::y2pitch(int y) const
      {
      const int total = (10 * 7 + 5) * KH;       // 75 Ganztonschritte
      y = total - y;
      int oct = (y / (7 * KH)) * 12;
      char kt[] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2,
            3, 3, 3, 3, 3, 3, 3,
            4, 4, 4, 4, 4, 4, 4, 4, 4,
            5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
            6, 6, 6, 6, 6, 6, 6,
            7, 7, 7, 7, 7, 7,
            8, 8, 8, 8, 8, 8, 8,
            9, 9, 9, 9, 9, 9,
            10, 10, 10, 10, 10, 10, 10,
            11, 11, 11, 11, 11, 11, 11, 11, 11, 11
            };
      return kt[y % 91] + oct;
      }

//---------------------------------------------------------
//   leaveEvent
//---------------------------------------------------------

void Piano::leaveEvent(QEvent*)
{
      if (keyDown != -1) {
            emit keyReleased(keyDown, shift);
            keyDown = -1;
      }
      emit pitchChanged(-1);
      setPitch(-1);
}

//---------------------------------------------------------
//   setPitch
//---------------------------------------------------------

void Piano::setPitch(int pitch)
{
      if (curPitch == pitch)
            return;
      curPitch = pitch;

      redraw();
}

//---------------------------------------------------------
//   viewMouseMoveEvent
//---------------------------------------------------------

void Piano::viewMouseMoveEvent(QMouseEvent* event)
{
      int pitch = y2pitch(event->y());
      emit pitchChanged(pitch);
      setPitch(pitch);

      if (button != Qt::NoButton) 
	  {
            int nk = y2pitch(event->y());
            if (nk < 0 || nk > 127)
                  nk = -1;
            if (nk != keyDown)
			{
                  if (keyDown != -1) 
				  {
                        emit keyReleased(keyDown, shift);
                  }
                  keyDown = nk;
                  if (keyDown != -1)
				  {
                        int velocity = event->x()*127/40;
                        //emit keyPressed(keyDown, shift);
                        emit keyPressed(keyDown, velocity>127 ? 127 : velocity, shift);
                  }
            }
      }
}

//---------------------------------------------------------
//   viewMousePressEvent
//---------------------------------------------------------

void Piano::viewMousePressEvent(QMouseEvent* event)
      {
      button = event->button();
      shift  = event->modifiers() & Qt::ShiftModifier;
      if (keyDown != -1) {
            emit keyReleased(keyDown, shift);
            keyDown = -1;
            }
      keyDown = y2pitch(event->y());
      if (keyDown < 0 || keyDown > 127) {
            keyDown = -1;
            }
      else {
            int velocity = event->x()*127/40;
            emit keyPressed(keyDown, velocity>127 ? 127 : velocity, shift); //emit keyPressed(keyDown, shift);
            }
      }

//---------------------------------------------------------
//   viewMouseReleaseEvent
//---------------------------------------------------------

void Piano::viewMouseReleaseEvent(QMouseEvent* event)
      {
      button = Qt::NoButton;
      shift = event->modifiers() & Qt::ShiftModifier;
      if (keyDown != -1) {
            emit keyReleased(keyDown, shift);
            keyDown = -1;
            }
      }

