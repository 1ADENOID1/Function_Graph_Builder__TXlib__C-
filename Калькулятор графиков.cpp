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
                txSelectFont("Arial", 10);
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

    void HID(bool *left, bool *right, bool *up, bool *down, bool *pageUp, bool *pageDown, bool *line, bool *parabola, bool *fracRational, bool *irrational, bool *sin, bool *cos, bool *tan)
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
        *sin=GetAsyncKeyState(53);
        *cos=GetAsyncKeyState(54);
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
        return (k/(l*x+m))+b;
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
        txCreateWindow(WIDTH+200, HEIGHT);
        txSetFillColor(TX_WHITE);
        txSetColor(TX_BLACK);
        txClear();
        bool up, down, left, right, pageUp, pageDown, line, parabola, fracRational, irrational, sin, cos, tan = false;
        int x0, y0;
        int graphSelect=1;
        double x, y, xNew, yNew, xNeg, yNeg, xNewNeg, yNewNeg, xOld, xOldNeg, yOld, yOldNeg;
        double scale = 1;

        double k = 1;
        double m = 0;
        double b = 0;
        double l = 1;
        double a, vv, c, d;

        char kCharInt[10];
        char mCharInt[10];
        char bCharInt[10];
        char lCharInt[10];

        char kCharDouble[10];
        char mCharDouble[10];
        char bCharDouble[10];
        char lCharDouble[10];

        x0=300;
        y0=300;

        Button kUp(670, 250, "k+");
        Button kDown(650, 250, "k-");
        Button mUp(670, 275, "m+");
        Button mDown(650, 275, "m-");
        Button bUp(670, 300, "b+");
        Button bDown(650, 300, "b-");
        Button lUp(670, 325, "l+");
        Button lDown(650, 325, "l-");

        while(TRUE)
        {
            HID(&left, &right, &up, &down, &pageUp, &pageDown, &line, &parabola, &fracRational, &irrational, &sin, &cos, &tan);

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
            if (pageUp)
            {
                scale=scale+0.2;

            }
            if ((pageDown) and (scale>=0.2))
            {
                scale=scale-0.2;
            }
            if (line)
            {
                x=0;
                graphSelect=1;
            }
            if (parabola)
            {
                x=0;
                graphSelect=2;
            }
            if (fracRational)
            {
                x=0;
                graphSelect=3;
            }
            if (irrational)
            {
                x=0;
                graphSelect=4;
            }
            if (sin)
            {
                x=0;
                graphSelect=5;
            }
            if (cos)
            {
                x=0;
                graphSelect=6;
            }
            if (tan)
            {
                x=0;
                graphSelect=7;
            }

            if (kUp.getPressed())
            {
                x=0;
                k=k+0.1;
                floor(k*10)/10;
            }
            if (kDown.getPressed())
            {
                x=0;
                k=k-0.1;
                floor(k*10)/10;
            }
            if (mUp.getPressed())
            {
                x=0;
                m=m+0.1;
                floor(m*10)/10;
            }
            if (mDown.getPressed())
            {
                x=0;
                m=m-0.1;
                floor(k*10)/10;
            }
            if (bUp.getPressed())
            {
                x=0;
                b=b+0.1;
                floor(b*10)/10;
            }
            if (bDown.getPressed())
            {
                x=0;
                b=b-0.1;
                floor(b*10)/10;
            }
            if (lUp.getPressed())
            {
                x=0;
                l=l+0.1;
                floor(l*10)/10;
            }
            if (lDown.getPressed())
            {
                x=0;
                l=l-0.1;
                floor(l*10)/10;
            }
            txSelectFont("Times New Roman", 15);


            txSetColor(RGB(0, 0, 255));
            txLine(0, y0, WIDTH, y0);
            txLine(x0, 0, x0, HEIGHT);
            txSetColor(TX_BLACK);
            int i=1;
            while(i<=(WIDTH-x0+300)/(1*10*scale))
            {
                txLine(x0+i*10*scale, 0, x0+i*10*scale, HEIGHT);
                txLine(x0-i*10*scale, 0, x0-i*10*scale, HEIGHT);
                txLine(0, y0+i*10*scale, WIDTH, y0+i*10*scale);
                txLine(0, y0-i*10*scale, WIDTH, y0-i*10*scale);
                txRectangle(WIDTH, 0, WIDTH+200, HEIGHT);
                i++;
            }
            kUp.drawButton();
            kDown.drawButton();
            mUp.drawButton();
            mDown.drawButton();

            txTextOut(650, 100, "k=");
            txTextOut(650+txGetTextExtentX("k="), 100, kCharInt);
            txTextOut(650+txGetTextExtentX("k=")+txGetTextExtentX(kCharInt), 100, ".");
            txTextOut(650+txGetTextExtentX("k=")+txGetTextExtentX(kCharInt)+txGetTextExtentX("."), 100, kCharDouble);
            txTextOut(650, 112, "m=");
            txTextOut(650+txGetTextExtentX("m="), 112, mCharInt);
            txTextOut(650+txGetTextExtentX("m=")+txGetTextExtentX(mCharInt), 112, ".");
            txTextOut(650+txGetTextExtentX("m=")+txGetTextExtentX(mCharInt)+txGetTextExtentX("."), 112, mCharDouble);
            if (graphSelect!=1)
            {
                bUp.drawButton();
                bDown.drawButton();
                lUp.drawButton();
                lDown.drawButton();
                txTextOut(650, 124, "b=");
                txTextOut(650+txGetTextExtentX("b="), 124, bCharInt);
                txTextOut(650+txGetTextExtentX("b=")+txGetTextExtentX(bCharInt), 124, ".");
                txTextOut(650+txGetTextExtentX("b=")+txGetTextExtentX(bCharInt)+txGetTextExtentX("."), 124, bCharDouble);
                txTextOut(650, 136, "l=");
                txTextOut(650+txGetTextExtentX("l="), 136, lCharInt);
                txTextOut(650+txGetTextExtentX("l=")+txGetTextExtentX(lCharInt), 136, ".");
                txTextOut(650+txGetTextExtentX("l=")+txGetTextExtentX(lCharInt)+txGetTextExtentX("."), 136, lCharDouble);
            }
            int j=0;
            x=0;
            xOld=0;
            xNeg=0;
            xOldNeg=0;
            bool firstRun=true;
            while(j<=(WIDTH-x0+300)/(1*0.1*scale))
            {
                floor(k*10)/10;
                floor(m*10)/10;
                floor(b*10)/10;
                floor(l*10)/10;
                x=x+(1*0.1);
                xNeg=xNeg-(1*0.1);
                if (graphSelect==1)
                {
                    y=lineFunc(-k, -m, x);
                    yNeg=lineFunc(-k, -m, xNeg);
                }
                if (graphSelect==2)
                {
                    y=parabolaFunc(-k, m, -b, l, x);
                    yNeg=parabolaFunc(-k, m, -b, l, xNeg);
                }
                if (graphSelect==3)
                {


                        if ((l*x+m)!=0)
                        {
                            y=fracRationalFunc(-k, m, -b, l, x);
                        }
                        if ((l*xNeg+m)!=0)
                        {
                            yNeg=fracRationalFunc(-k, m, -b, l, xNeg);
                        }

                }
                if (graphSelect==4)
                {
                    if ((l*x+m)>=0)
                    {
                        y=irrationalFunc(-k, m, -b, l, x);
                    }
                    if ((l*xNeg+m)>=0)
                    {
                        yNeg=irrationalFunc(-k, m, -b, l, xNeg);
                    }
                }
                if (graphSelect==5)
                {
                    y=sinFunc(-k, m, -b, l, x);
                    yNeg=sinFunc(k, -m, -b, l, x);
                }
                if (graphSelect==6)
                {
                    y=cosFunc(-k, m, -b, l, x);
                    yNeg=cosFunc(-k, -m, -b, l, x);
                }
                if (graphSelect==7)
                {
                    if ((x!=M_PI/2) or (x!=(-(M_PI/2))))
                    {
                        y=tanFunc(-k, m, -b, l, x);
                    }
                    if ((xNeg!=M_PI/2) or (xNeg!=(-(M_PI/2))))
                    {
                        yNeg=tanFunc(k, -m, -b, l, x);
                    }
                }
                xNew=x*10*scale+x0;
                yNew=y*10*scale+y0;
                xNewNeg=xNeg*10*scale+x0;
                yNewNeg=yNeg*10*scale+y0;
                if (firstRun)
                {
                    yOld=yNew;
                    yOldNeg=yNewNeg;
                }
                firstRun=false;

                //cout << xNew << endl;
                //cout << m << endl;
                txSetColor(TX_RED);
                if ((yNew>=0) and (yNew<=HEIGHT))
                {
                    txSetPixel(xNew, yNew, TX_RED);
                     //txLine(xOld, yOld, xNew, yNew);
                     xOld=xNew;
                     yOld=xNew;
                }
                if ((yNewNeg>=0) and (yNewNeg<=HEIGHT))
                {
                    txSetPixel(xNewNeg, yNewNeg, TX_RED);
                    //txLine(xOldNeg, yOldNeg, xNewNeg, yNewNeg);
                    xOldNeg=xNewNeg;
                    yOldNeg=yNewNeg;
                }
                //txSetColor(TX_RED);


                txSetColor(TX_BLACK);



                j++;

            }

            _itoa(trunc(k), kCharInt, 10);
            _itoa(trunc(m), mCharInt, 10);
            _itoa(trunc(b), bCharInt, 10);
            _itoa(trunc(l), lCharInt, 10);

            _itoa(abs(modf(k, &a)*10) , kCharDouble, 10);
            _itoa(abs(modf(m, &vv)*10), mCharDouble, 10);
            _itoa(abs(modf(b, &c)*10), bCharDouble, 10);
            _itoa(abs(modf(l, &d)*10), lCharDouble, 10);

            txSleep(10);
            txClear();

        }


        return 0;
    }
    //=============================================ÌÓÒÍÛÉ ÌÐÀÊ 229
    //=============================================ÌÓÒÍÛÉ ÌÐÀÊ 229
    //=============================================ÌÓÒÍÛÉ ÌÐÀÊ 229
    //=============================================ÌÓÒÍÛÉ ÌÐÀÊ 229
    //=============================================ÌÓÒÍÛÉ ÌÐÀÊ 229
