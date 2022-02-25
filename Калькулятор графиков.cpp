    //===================================Coded by 1ADENOID1==================================
    //===================================Coded by 1ADENOID1==================================
    //===================================Coded by 1ADENOID1==================================
    //===================================Coded by 1ADENOID1==================================
    //===================================Coded by 1ADENOID1==================================
    //===================================Coded by 1ADENOID1==================================
    //===================================Coded by 1ADENOID1==================================
    //===================================Coded by 1ADENOID1==================================



    //===================================Version: alpha 0.1.0================================



    #include "TXlib.h"
    #include <cmath>
    #include <cstdio>

    using namespace std;

    const int HEIGHT=600;
    const int WIDTH=600;

    class Button
    {
        private:
            int x0, y0;
            char text0[255];
            bool pressed=false;
        public:
            Button(int x, int y, char text[255])
            {
                x0=x;
                y0=y;
                strcpy(text0, text);
            }
            void setX(int x)
            {
                x0=x;
            }
            void setY(int y)
            {
                y0=y;
            }
            void setText(char text[255])
            {
                strcpy(text0, text);
            }

            bool getPressed()
            {
                return pressed;
            }
            void drawButton()
            {
                txSetColor(TX_GREEN);
                txSelectFont("Arial", 12);
                txRectangle(x0, y0, x0+10+txGetTextExtentX(text0), y0+6+txGetTextExtentY(text0));
                txTextOut(x0+5, y0+3, text0);
                pressCheck();
            }
            void pressCheck()
            {
                if ((x0<=txMouseX()) and (x0+10+txGetTextExtentX(text0)>=txMouseX()) and (y0<=txMouseY()) and (y0+6+txGetTextExtentY(text0)>=txMouseY()) and (not((txMouseButtons() & 1)==0)))
                {
                    pressed=true;
                }
                else
                {
                    pressed=false;
                }
            }

    };

    void HID(bool *left, bool *right, bool *up, bool *down, bool *pageUp, bool *pageDown, bool *line, bool *parabola, bool *fracRational, bool *irrational, bool *sinus, bool *cosinus, bool *tan)
    {
        *left=GetAsyncKeyState(VK_LEFT);
        *right=GetAsyncKeyState(VK_RIGHT);
        *up=GetAsyncKeyState(VK_UP);
        *down=GetAsyncKeyState(VK_DOWN);
        *pageUp=GetAsyncKeyState(VK_NEXT);
        *pageDown=GetAsyncKeyState(VK_PRIOR);
        *line=GetAsyncKeyState(49);
        *parabola=GetAsyncKeyState(50);
        *fracRational=GetAsyncKeyState(51);
        *irrational=GetAsyncKeyState(52);
        *sinus=GetAsyncKeyState(53);
        *cosinus=GetAsyncKeyState(54);
        *tan=GetAsyncKeyState(55);
    }

    double lineFunc(double k, double m, double x)
    {
        return k*x+m;
    }

    double parabolaFunc(double k, double m, double b, double l, double x)
    {
        return k*pow((l*x+m), 2)+b;
    }

    double fracRationalFunc(double k, double m, double b, double l, double x)
    {

        return floor(((k/(l*x+m))+b)*1000)/1000;

    }

    double irrationalFunc(double k, double m, double b, double l, double x)
    {
        return (k*sqrt(l*x+m))+b;
    }

    double sinFunc(double k, double m, double b, double l, double x)
    {
        return (k*sin(l*x+m))+b;
    }

    double cosFunc(double k, double m, double b, double l, double x)
    {
        return (k*cos(l*x+m))+b;
    }

    double tanFunc(double k, double m, double b, double l, double x)
    {
        return (k*tan(l*x+m))+b;
    }
    int main()
    {
        setlocale(LC_ALL, "Russian");

        txCreateWindow(WIDTH+200, HEIGHT+60);
        txDisableAutoPause();
        txSetFillColor(TX_WHITE);
        txSetColor(TX_BLACK);
        txClear();

        bool up, down, left, right, pageUp, pageDown, line, parabola, fracRational, irrational, sinus, cosinus, tan = false;
        int x0, y0;
        int graphSelect=1;
        double x, y, xNew, yNew, xNeg, yNeg, xNewNeg, yNewNeg, xOld, xOldNeg, yOld, yOldNeg;
        double scale = 3;

        double k = 1;
        double m = 0;
        double b = 0;
        double l = 1;

        char kCharInt[100];
        char mCharInt[100];
        char bCharInt[100];
        char lCharInt[100];
        char iCharInt[100000];
        char uravnenie[100000];

        x0=300;
        y0=300;

        Button kUp(675, 245, "k+");
        Button kDown(650, 245, "k-");
        Button mUp(675, 270, "m+");
        Button mDown(650, 270, "m-");
        Button bUp(675, 295, "b+");
        Button bDown(650, 295, "b-");
        Button lUp(675, 320, "l+");
        Button lDown(650, 320, "l-");

        Button lineSelect(650, 340, "      прямая y=kx+m      ");
        Button parabSelect(650, 360, " парабола y=k(lx+m)^2+b  ");
        Button fracRationalSelect(650, 380, " гипербола y=k/(lx+m)+b  ");
        Button irrationalSelect(650, 400, " корень y=k*sqrt(lx+m)+b ");
        Button sinSelect(650, 420, "  синус y=k*sin(lx+m)+b  ");
        Button cosSelect(650, 440, " косинус y=k*cos(lx+m)+b ");
        Button tanSelect(650, 460, "  тагенс y=k*tg(lx+m)+b  ");

        txBegin();

        while(TRUE)
        {
            HID(&left, &right, &up, &down, &pageUp, &pageDown, &line, &parabola, &fracRational, &irrational, &sinus, &cosinus, &tan);

            if (left)
            {
                x0--;
            }
            if (right)
            {
                x0++;
            }
            if (up)
            {
                y0--;
            }
            if (down)
            {
                y0++;
            }
            if ((pageUp) and (scale<=15))
            {
                scale=scale+0.2;
            }
            if ((pageDown) and (scale>=2))
            {
                scale=scale-0.2;
            }
            if ((line) or (lineSelect.getPressed()))
            {
                x=0;
                graphSelect=1;
            }
            if ((parabola) or (parabSelect.getPressed()))
            {
                x=0;
                graphSelect=2;
            }
            if ((fracRational) or (fracRationalSelect.getPressed()))
            {
                x=0;
                graphSelect=3;
            }
            if ((irrational) or (irrationalSelect.getPressed()))
            {
                x=0;
                graphSelect=4;
            }
            if ((sinus) or (sinSelect.getPressed()))
            {
                x=0;
                graphSelect=5;
            }
            if ((cosinus) or (cosSelect.getPressed()))
            {
                x=0;
                graphSelect=6;
            }
            if ((tan) or (tanSelect.getPressed()))
            {
                x=0;
                graphSelect=7;
            }

            if (kUp.getPressed())
            {
                x=0;
                k=k+0.1;

            }
            if (kDown.getPressed())
            {
                x=0;
                k=k-0.1;

            }
            if (mUp.getPressed())
            {
                x=0;
                m=m+0.1;

            }
            if (mDown.getPressed())
            {
                x=0;
                m=m-0.1;

            }
            if (bUp.getPressed())
            {
                x=0;
                b=b+0.1;

            }
            if (bDown.getPressed())
            {
                x=0;
                b=b-0.1;

            }
            if (lUp.getPressed())
            {
                x=0;
                l=l+0.1;

            }
            if (lDown.getPressed())
            {
                x=0;
                l=l-0.1;
            }

            txSelectFont("Times New Roman", 15);

            txSetColor(RGB(0, 0, 255), 4);
            txLine(0, y0, WIDTH, y0);
            txLine(x0, 0, x0, HEIGHT);
            txSetColor(TX_BLACK, 3);
            int i=1;
            int i1;


            txSelectFont("Arial", 7*scale);
            while(i<=(WIDTH-x0+300)/(1*10*scale))
            {
                i1=-i;
                txLine(x0+i*10*scale, 0, x0+i*10*scale, HEIGHT);
                sprintf(iCharInt, "%d", i);
                txTextOut(x0+i*10*scale, y0, iCharInt);
                sprintf(iCharInt, "%d", i1);
                txLine(x0-i*10*scale, 0, x0-i*10*scale, HEIGHT);
                txTextOut(x0-i*10*scale, y0, iCharInt);
                txLine(0, y0+i*10*scale, WIDTH, y0+i*10*scale);
                sprintf(iCharInt, "%d", i);
                txTextOut(x0, y0-i*10*scale, iCharInt);
                txLine(0, y0-i*10*scale, WIDTH, y0-i*10*scale);
                sprintf(iCharInt, "%d", i1);
                txTextOut(x0, y0+i*10*scale, iCharInt);

                i++;
            }
            txSetColor(TX_BLACK);
            txSelectFont("Times New Roman", 15);

            txTextOut(WIDTH/2, HEIGHT-30, "Coded by 1ADENOID1          Version: alpha 0.1.0");

            int j=0;
            x=0;
            xOld=x0;
            xNeg=0;
            xOldNeg=x0;
            bool firstRun=true;
            bool firstRunNeg=true;

            while(j<=(WIDTH-x0+300)/(1*0.1*scale))
            {
                bool drawer=true;
                bool drawerNeg=true;

                if (graphSelect==1)
                {
                    sprintf(uravnenie, "y=%fx+%f", k, m);
                    y=lineFunc(-k, -m, x);
                    yNeg=lineFunc(-k, -m, xNeg);
                }
                if (graphSelect==2)
                {
                    sprintf(uravnenie, "y=%f*(%fx+%f)^2+%f", k, l, m, b);
                    y=parabolaFunc(-k, m, -b, l, x);
                    yNeg=parabolaFunc(-k, m, -b, l, xNeg);
                }
                if (graphSelect==3)
                {
                    sprintf(uravnenie, "y=%f*(1/(%fx+%f))+%f", k, l, m, b);
                    if (abs(((l*x)+m))>=0.00001)
                    {
                        y=fracRationalFunc(-k, m, -b, l, x);
                    }
                    if ((((l*x)+m)>=-0.03) and (((l*x)+m)<=0.03))
                    {
                        drawer=false;
                    }
                    if (abs(((l*xNeg)+m))>=0.00001)
                    {
                        yNeg=fracRationalFunc(-k, m, -b, l, xNeg);
                    }
                    if ((((l*xNeg)+m)>=-0.03) and (((l*xNeg)+m)<=0.03))
                    {
                        drawerNeg=false;
                    }
                }
                if (graphSelect==4)
                {
                    sprintf(uravnenie, "y=%f*sqrt(%fx+%f)+%f", k, l, m, b);
                    if ((l*x+m)>=0.0)
                    {
                        y=irrationalFunc(-k, m, -b, l, x);
                    }
                    else
                    {
                        drawer=false;
                        y=0-b;
                    }
                    if ((l*xNeg+m)>=0.0)
                    {
                        yNeg=irrationalFunc(-k, m, -b, l, xNeg);
                    }
                    else
                    {
                        drawerNeg=false;
                        yNeg=0-b;
                    }
                }
                if (graphSelect==5)
                {
                    sprintf(uravnenie, "y=%f*sin(%fx+%f)+%f", k, l, m, b);
                    y=sinFunc(-k, m, -b, l, x);
                    yNeg=sinFunc(-k, m, -b, l, xNeg);
                }
                if (graphSelect==6)
                {
                    sprintf(uravnenie, "y=%f*cos(%fx+%f)+%f", k, l, m, b);
                    y=cosFunc(-k, m, -b, l, x);
                    yNeg=cosFunc(-k, m, -b, l, xNeg);
                }


                if (graphSelect==7)
                {
                    sprintf(uravnenie, "y=%f*tg(%fx+%f)+%f", k, l, m, b);
                    if (abs(cos(l*x+m))>=0.0000000000000001)
                    {
                        y=tanFunc(-k, m, -b, l, x);
                    }
                    if ((cos(l*x+m)>=-0.02) and (cos(l*x+m)<=0.02))
                    {
                        drawer=false;
                    }
                    if (abs(cos(l*xNeg+m))>=0.0000000000000001)
                    {

                       yNeg=tanFunc(-k, m, -b, l, xNeg);
                    }
                    if  ((cos(l*xNeg+m)>=-0.02) and (cos(l*xNeg+m)<=0.02))
                    {
                        drawerNeg=false;
                    }
                }

                xNew=round(x*10*scale+x0);
                yNew=round(y*10*scale+y0);
                xNewNeg=round(xNeg*10*scale+x0);
                yNewNeg=round(yNeg*10*scale+y0);

                if (firstRun)
                {
                    yOld=yNew;
                }
                if (firstRunNeg)
                {
                    yOldNeg=yNewNeg;
                }

                txSetColor(TX_RED, 5);

                if ((yNew>=-100000) and (yNew<=HEIGHT+100000) and (drawer))
                {
                     txLine((round(xOld)), (round(yOld)), (round(xNew)), (round(yNew)));
                }

                if ((yNewNeg>=-100000) and (yNewNeg<=HEIGHT+100000) and (drawerNeg))
                {
                    txLine((round(xOldNeg)), (round(yOldNeg)), (round(xNewNeg)), (round(yNewNeg)));
                }

                    xOldNeg=xNewNeg;
                    yOldNeg=yNewNeg;

                    xOld=xNew;
                    yOld=yNew;

                firstRun=false;
                firstRunNeg=false;
                x=x+0.01;
                xNeg=xNeg-0.01;

                txSetColor(TX_BLACK);
                j++;
            }

            txRectangle(WIDTH, 0, WIDTH+200, HEIGHT);
            txRectangle(0, HEIGHT, WIDTH+200, HEIGHT+60);

            kUp.drawButton();
            kDown.drawButton();
            mUp.drawButton();
            mDown.drawButton();
            txSelectFont("Arial", 23);
            txTextOut(650, 50, "k=");
            txTextOut(650+txGetTextExtentX("k="), 50, kCharInt);

            txTextOut(650, 75, "m=");
            txTextOut(650+txGetTextExtentX("m="), 75, mCharInt);

            txSelectFont("Arial", 42);
            txTextOut(20, 610, uravnenie);

            if (graphSelect!=1)
            {
                bUp.drawButton();
                bDown.drawButton();
                lUp.drawButton();
                lDown.drawButton();
                txSelectFont("Arial", 23);
                txTextOut(650, 100, "b=");
                txTextOut(650+txGetTextExtentX("b="), 100, bCharInt);

                txTextOut(650, 125, "l=");
                txTextOut(650+txGetTextExtentX("l="), 125, lCharInt);
            }

            lineSelect.drawButton();
            parabSelect.drawButton();
            fracRationalSelect.drawButton();
            irrationalSelect.drawButton();
            sinSelect.drawButton();
            cosSelect.drawButton();
            tanSelect.drawButton();

            sprintf(kCharInt, "%f", k);
            sprintf(mCharInt, "%f", m);
            sprintf(lCharInt, "%f", l);
            sprintf(bCharInt, "%f", b);

            if (GetAsyncKeyState(VK_ESCAPE))
            {
                return 0;
            }

            txSleep(10);
            txClear();
        }
        txEnd();
        return 0;
    }
    //=============================================мутный мрак 229
    //=============================================мутный мрак 229
    //=============================================мутный мрак 229
    //=============================================мутный мрак 229
    //=============================================мутный мрак 229
