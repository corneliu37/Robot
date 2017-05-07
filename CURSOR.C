                   

		   /* CONTROL OF AN AUTONOMOUS ROBOT USING A GENO-FUZZY TECHNIQUE    */


#include <windows.h>
#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include <time.h>




#define LUNGCROMOZOM  114 
#define LUNGENA 1
#define BAZA 2
#define NRPOPPAR 10
#define NRPOPCOP 10
#define NRPOPTOT 20 
#define NRVARLING1 2
#define NRVARLING2 6
#define MARE  0
#define MIC   1
#define MARE  0
#define MIC   1

typedef struct{
 int a[6];
}co;

typedef struct{
 co b[6]; 
}cod;

cod c[2];


#define IDM_EXIT                        202
#define IDM_STATE1                      610
#define IDM_STATE2                      611
#define IDM_STATE3                      612
#define IDM_STATE4                      613
   
#define IDM_ABOUT                       301



typedef struct
{
    long double xleft_up; 
    long double yleft_up;
    long double xright_down;
    long double yright_down;
    long double xCentru;
    long double yCentru;
}OBSTACOL;

typedef struct
{
    long double xleft_up;
    long double yleft_up;
    long double xright_down;
    long double yright_down;
    long double xCentru;
    long double yCentru;
}ROBOT;   

              
typedef struct
{
   unsigned long Fitness;
   int   cromo[LUNGCROMOZOM];
}CROMOZOM;

int i,pas;

typedef struct{
      int x[300];
      int y[300];

}traiectorie ;

typedef struct{ 
  CROMOZOM l;  
       int m;
}inter ;  


typedef struct{
  unsigned long ob[650];
}roata ;



typedef struct 
{
   float fCentroid;
   float fDispersieS;
   float fDispersieC;
   float fDispersieD;
}VAR_LINGVISTICA ;

typedef struct
{
   int   iVarLingvistica ;
   float fGradApartenenta;
}TIP_APARTENENTA;   

typedef struct 
{
   float fDeltaFi;
}CRISP_OUT;   



typedef struct
{                
   
   int dx;
   int dy;
}Comanda;

int  x_final,ri;
int  y_final,ti;
int i;
unsigned long total1;   
int tip[3];
HWND hWnd;
OBSTACOL obs[30];
ROBOT rob;                  
HANDLE hInst;
char str[150];                          // general-purpose string buffer
CROMOZOM poppar[10];
CROMOZOM popcop[10];
CROMOZOM poptot[20];
VAR_LINGVISTICA  pvo[2];
VAR_LINGVISTICA  pvm[6];
VAR_LINGVISTICA  pvn[6];
unsigned long n=0;
int logic;                 
              
                    
                             
int com,t;
int x1;
int y1;
int  fInput;
int nvarling ;
int initial;
unsigned long lovit;
unsigned long d;
roata obst[10];  
int a1,t1;
int poz;
TIP_APARTENENTA TipVar1;
TIP_APARTENENTA TipVar2;
int pas;
traiectorie  vector[10];
int vertical;
int con=11;
int nr,rem,mer;
int xmem ,ymem;

typedef struct
{ 
  float fvDeplasare[2];
}DEPLASARE;  




int FAR PASCAL _export About(HWND ,UINT,WPARAM,LPARAM,int,int,int,int );
int PASCAL WinMain(HANDLE, HANDLE, LPSTR, int);
BOOL   InitApplication(HANDLE);
BOOL  InitInstance(HANDLE, int);
long FAR PASCAL _export MainWndProc(HWND, UINT, WPARAM, LPARAM);
void FAR PASCAL Sortare (CROMOZOM*);
OBSTACOL* FAR PASCAL  Harta1( HWND,OBSTACOL*,ROBOT);
OBSTACOL* FAR PASCAL  Harta2(HWND,OBSTACOL*,ROBOT);
float FAR PASCAL  Go2(ROBOT,HWND,traiectorie*,CROMOZOM*,CROMOZOM*,LPARAM,WPARAM);
FAR PASCAL Afiseaza_Drum2(HWND,OBSTACOL*,ROBOT ,int,traiectorie*);
OBSTACOL* FAR PASCAL  Harta3(HWND,OBSTACOL*,ROBOT);
int FAR PASCAL  Go3(ROBOT,HWND,traiectorie*,CROMOZOM*,CROMOZOM*,LPARAM,WPARAM);
FAR PASCAL Afiseaza_Drum3(HWND,OBSTACOL*,ROBOT ,int,traiectorie*);
TIP_APARTENENTA  FAR PASCAL Fuzificare (int ,VAR_LINGVISTICA* ,int,HWND);
CROMOZOM* FAR PASCAL Incrucisare (CROMOZOM*,HWND);
cod* FAR PASCAL Load (CROMOZOM*,cod*,int,HWND);
VAR_LINGVISTICA* L_init_var_ling(VAR_LINGVISTICA* ,VAR_LINGVISTICA* ,VAR_LINGVISTICA*,HWND) ;
unsigned long FAR PASCAL CalculezFitnes(int,CROMOZOM*,OBSTACOL*,ROBOT,int,int);
CROMOZOM* FAR PASCAL Ruleta(CROMOZOM*,HWND);
CROMOZOM* FAR PASCAL Mutatie (unsigned long ,CROMOZOM*,HWND );
int* FAR PASCAL Intermediar1(int*,OBSTACOL*,int ,int,ROBOT,TIP_APARTENENTA,TIP_APARTENENTA,int,HWND,unsigned long);
float FAR PASCAL  Go(ROBOT,HWND,traiectorie*,CROMOZOM*,CROMOZOM*,LPARAM,WPARAM);
CROMOZOM* FAR PASCAL genetic(int,HWND,unsigned long);
CROMOZOM* FAR PASCAL Combinare(CROMOZOM*,CROMOZOM*,HWND);
traiectorie* FAR PASCAL Deplasare(ROBOT,Comanda,int ,int,int,int,traiectorie*,int);
FAR PASCAL Afiseaza_Drum(HWND,OBSTACOL*,ROBOT ,int,traiectorie*);
int FAR PASCAL test(OBSTACOL*,ROBOT,int,int,unsigned long,int);
int FAR PASCAL Intermediar (int ,int,OBSTACOL*);
FAR PASCAL Load_genetic_init(CROMOZOM*);
VAR_LINGVISTICA* FAR PASCAL Modific_var_ling (CROMOZOM*,int,VAR_LINGVISTICA*,VAR_LINGVISTICA*,VAR_LINGVISTICA*,HWND);
cod* FAR PASCAL LoadInitial (cod*);
Comanda FAR PASCAL Com(int,HWND);
ROBOT  Pozitie(ROBOT,int);
ROBOT FAR PASCAL  Sa_stie_si_rob(ROBOT,traiectorie*,int,int,HWND);
unsigned long FAR PASCAL CalculezFitnes1(int,CROMOZOM*,OBSTACOL*,ROBOT,int,int);
int FAR PASCAL test1(ROBOT);
CROMOZOM* calcularefitnesmosad(CROMOZOM*,CROMOZOM*);




int PASCAL WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow)
HANDLE hInstance;
HANDLE hPrevInstance;
LPSTR lpCmdLine;
int nCmdShow;
{
    MSG msg;
 
    if (!hPrevInstance)
        if (!InitApplication(hInstance)) 
            return (FALSE);

    if (!InitInstance(hInstance, SW_SHOWMAXIMIZED))
        return (FALSE);

    while (GetMessage(&msg, NULL, NULL, NULL))
    { 
      
       
        TranslateMessage(&msg);
        DispatchMessage(&msg);
         
    }
    return (msg.wParam);
}







BOOL   InitApplication(hInstance) 
HANDLE hInstance;
{
    
    WNDCLASS  wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(hInstance, "bullseye");
    wc.hbrBackground = GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName =  "MYMENU";
    wc.lpszClassName = "CursorWClass";

    return (RegisterClass(&wc));
} 




BOOL   InitInstance(hInstance, nCmdShow)  
HANDLE          hInstance;              
int             nCmdShow;
{
    HWND            hWnd;

    hInst = hInstance;

    hWnd = CreateWindow("CursorWClass",
                        "FINAL PROJECT",
                        WS_MAXIMIZE | WS_OVERLAPPEDWINDOW|WS_VSCROLL|WS_HSCROLL,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                         NULL,
                        NULL,
                        hInstance,
                         NULL);

    if (!hWnd)
        return (FALSE);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return (TRUE);

}




long FAR PASCAL _export MainWndProc(hWnd, message, wParam, lParam)
HWND hWnd;
UINT message;
WPARAM wParam;
LPARAM lParam;                                

{
   int i,xMouse ,yMouse;
   short nLength;
   char szBuffer[40];
   HDC hDC;
   PAINTSTRUCT ps;


   
    switch (message)
    {    
	case WM_COMMAND:
	    if (wParam == IDM_STATE3)
            {   
			
			  Harta1(hWnd,obs,rob);

			  Go(rob,hWnd,vector,popcop,poppar,lParam,wParam);
			 
		   break;
            } 
	    else
		if  (wParam == IDM_STATE2)
		  {

		    	 Harta2(hWnd,obs,rob);
			 Go2(rob,hWnd,vector,popcop,poppar,lParam,wParam);


                   break;
                  }
		else
		   if (wParam == IDM_STATE1)
		     {
		      Harta3(hWnd,obs,rob);
                      Go3(rob,hWnd,vector,popcop,poppar,lParam ,wParam);

                      break;
		     } 

//             return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return (NULL);
}


//  harta 1

OBSTACOL* FAR PASCAL Harta1(hWnd ,obs,rob)
HWND hWnd;
OBSTACOL obs[30];
ROBOT rob;

{
       HDC hDC;
     int i;
     short nLength;
     char szBuffer[100];  

     
     
      
	obs[0].xleft_up = 190;
        obs[0].yleft_up = 110;
        obs[0].xright_down =250; 
        obs[0].yright_down =170; 
        obs[0].xCentru = 220;
        obs[0].yCentru = 140;
        
 
        obs[1].xleft_up =400;	
        obs[1].yleft_up =210; 
        obs[1].xright_down =460; 
        obs[1].yright_down =270; 
        obs[1].xCentru = 430;
        obs[1].yCentru = 240;
        
         
        obs[2].xleft_up =40;	
        obs[2].yleft_up =216; 
        obs[2].xright_down =100; 
        obs[2].yright_down =276; 
        obs[2].xCentru = 70;
	obs[2].yCentru = 246;
        
      
        obs[3].xleft_up =40;	
        obs[3].yleft_up =370; 
        obs[3].xright_down =100; 
        obs[3].yright_down =430; 
        obs[3].xCentru = 70;
        obs[3].yCentru = 400;
        
        obs[4].xleft_up =150;	
        obs[4].yleft_up =330; 
        obs[4].xright_down =210; 
        obs[4].yright_down =390; 
        obs[4].xCentru = 180;
        obs[4].yCentru = 360;
        
        obs[5].xleft_up =530;	
        obs[5].yleft_up =140; 
        obs[5].xright_down =590; 
        obs[5].yright_down =200; 
        obs[5].xCentru = 560;
        obs[5].yCentru = 170 ;
         
        obs[6].xleft_up =610;	
        obs[6].yleft_up =210; 
        obs[6].xright_down =670; 
        obs[6].yright_down =270;
        obs[6].xCentru = 640;
	obs[6].yCentru = 240;
         
      
        obs[7].xleft_up =445;	
        obs[7].yleft_up =130;
        obs[7].xright_down =505; 
        obs[7].yright_down =190;
        obs[7].xCentru = 475;
        obs[7].yCentru = 160;  
        
	obs[8].xleft_up =429;
        obs[8].yleft_up =396; 
        obs[8].xright_down =489; 
        obs[8].yright_down =456; 
        obs[8].xCentru = 459;
        obs[8].yCentru = 426;
        
        obs[9].xleft_up =510;	
        obs[9].yleft_up =250; 
        obs[9].xright_down =570; 
        obs[9].yright_down =310; 
        obs[9].xCentru = 540;
	obs[9].yCentru =280;


	obs[10].xleft_up =  110;
        obs[10].yleft_up =  130;
	obs[10].xright_down = 170; 
	obs[10].yright_down = 190; 
        obs[10].xCentru =  140; 
        obs[10].yCentru =  160; 






	   
     hDC = GetDC(hWnd);
 
     MoveTo(hDC,10,25);
     LineTo(hDC,10,480);
     LineTo(hDC,750,480);
     LineTo(hDC,750,25);   
     LineTo(hDC,10,25);
     nLength = sprintf(szBuffer,"Terrain Map 3 ");
     TextOut (hDC,352,5,szBuffer,nLength);

        for (i=0;i<30;i++) 
	  Ellipse(hDC,obs[i].xleft_up , obs[i].yleft_up , obs[i].xright_down , obs[i].yright_down ) ;







        ReleaseDC (hWnd,hDC ); 
	return obs;
}  

   
      

  
int FAR PASCAL _export About(hWnd, message, wParam, lParam,OrgX,OrgY,PrevY,PrevX)
HWND hWnd;
UINT message;
WPARAM wParam;
LONG lParam;
int OrgX;
int OrgY;
int PrevY;
int PrevX;

{
    switch (message)
    {
        case WM_PAINT:
           {
               int x=OrgX;
               int y=OrgY;
               int z=PrevY;
               int b=PrevX;
 
           
           HDC hDC;
           PAINTSTRUCT     ps;
          
       
                  hDC = BeginPaint (hWnd, &ps);
                  if (x != y|| z != b)
                    {
                      MoveTo(hDC, x, y);
                      LineTo(hDC, z , y);
                      LineTo(hDC, z, b);
                      LineTo(hDC, z, y);
                      LineTo(hDC, x, b);
                    }
                  EndPaint (hWnd, &ps);
	     }
            
        }    
        return 1;    
} 


float  FAR PASCAL Go (rob,hWnd,vector,popcop,poppar,lParam,wParam)
ROBOT rob;
HWND hWnd;
traiectorie vector[10];
CROMOZOM popcop[10];
CROMOZOM poppar[10];
LPARAM lParam;
WPARAM wParam;
{
   short nLength;
   int z;
   char szBuffer[100];
   HDC hDC;
   Comanda m;
   int i,j,i1;
   int stop,moc,sin;
   int s,s1,s2;
   int top[3];
   int l1,m1,n1,k;
   unsigned long f1,f;
   MSG msg;
   int f2;
   struct time t1,t2;
   unsigned long  m11,m2;
   int xMouse,yMouse;
   PAINTSTRUCT ps;
   POINT pon;
   HPEN  hpen,hpenOld ; 
   int ionut,camelia;
   int tut=0;



do {
     if (tut <1)
       {
  	   while(  PeekMessage(&msg, hWnd,WM_MOUSEFIRST,WM_MOUSELAST, PM_NOYIELD|PM_REMOVE) )
	    {
	      if (msg.message ==WM_LBUTTONDOWN)
		{
                  
		  xMouse = LOWORD(msg.lParam);
		  yMouse = HIWORD(msg.lParam);
		  ri = xMouse;
                  ti = yMouse;
		  rob.xleft_up = xMouse-20;
                  rob.yleft_up = yMouse-20;
                  rob.xright_down = xMouse +20;
                  rob.yright_down = yMouse +20;
                  rob.xCentru = xMouse;
		  rob.yCentru = yMouse;
		  hDC =GetDC(hWnd);
		  Ellipse(hDC,rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down ) ;
		  ReleaseDC(hWnd,hDC);   
                  tut=1;     
                 };
	      TranslateMessage(&msg);
              DispatchMessage(&msg);
	    };
	}
      else
        {
	    while(  PeekMessage(&msg, hWnd,WM_MOUSEFIRST,WM_MOUSELAST, PM_NOYIELD|PM_REMOVE) )
	     {
	        if (msg.message ==WM_LBUTTONDOWN)
		  {
                  
		     x_final = LOWORD(msg.lParam);
		     y_final = HIWORD(msg.lParam);
		   
		     hDC =GetDC(hWnd);
		     SetPixel(hDC,x_final,y_final,RGB(0,0,0) );
		     ReleaseDC(hWnd,hDC);
               
	      
                     tut=2;     
                  };
	        TranslateMessage(&msg);
                DispatchMessage(&msg);
            };
         }



}
while (tut < 2);


   Reluare :

     
   n=0;
   for (i=0;i<10;i++)
      {
       poppar[i].Fitness = 0;
       popcop[i].Fitness = 0 ;
      };
   L_init_var_ling(pvo,pvm,pvn,hWnd); 

   Load_genetic_init(poppar);
 
   LoadInitial(c);

	 
     

   for(i=0;i<10;i++)
     poppar[i].Fitness =0;
   pas =0;
     for(i=0;i<10 ;i++)
       {
         for(j=0;j<300;j++)
           { 
   	  if(j==0)
	    {
	     if(logic != 1)
              {
	      vector[i].x[0] =ri; 
	      vector[i].y[0] =ti;
	      }
	     else
	      {
	      vector[i].x[0] = xmem;
	      vector[j].y[0] = ymem; 
	       }
	    }
 	   else
  	    {
	      vector[i].x[j] = 0;
	      vector[i].y[j] = 0;
             }
           };
        };
    Sa_stie_si_rob(rob,vector,pas,0,hWnd);
    pas =1;
    ionut = 0;


    do
     {
	  
	   Intermediar1(tip,obs,x1,y1,rob,TipVar1,TipVar2,vertical,hWnd,d);

	  

           com = c[tip[2]].b[tip[1]].a[tip[0]];
    	   m= Com (com,hWnd);
	 
      
           Deplasare (rob,m,0,pas,x1,y1,vector,poz);
	 
	   rob=  Sa_stie_si_rob(rob,vector,pas,0,hWnd);

	   f1= CalculezFitnes1 (0,poppar,obs,rob,x1,y1);
	   pas=pas+1;   


//1
	if (     (ri >= x_final)&(ti <= y_final)&( rob.xCentru <= (x_final+10) )&( rob.yCentru >= (y_final-6) ) )
	           ionut =1;     
//2
	if (     (ri >= x_final)&(ti >= y_final)&( rob.xCentru <= (x_final+15) )&( rob.yCentru <= (y_final+15) ) )
		   ionut =1;
//0		        
	if (     (ri <= x_final)&(ti <= y_final)&( rob.xCentru >= (x_final-10) )&( rob.yCentru >= (y_final-6) ) )
		   ionut =1;
//3		        
	if (     (ri <= x_final)&(ti >= y_final)&( rob.xCentru >= (x_final-15) )&( rob.yCentru <= (y_final+15) ) )
	           ionut =1;     


      }
   while (ionut != 1);
   for (i=0;i<10;i++)
          poppar[i].Fitness = f1 ;
    if (poppar[0].Fitness ==0)
      {
	
		Afiseaza_Drum(hWnd,obs,rob,0,vector);
           //     goto Fight;
   	   	goto Exit;
      };
     
     
	          
    n=0;
    initial =0;
    
   do {



             n=n+1;
	     for(i=0;i<10;i++)
	         for(j=0;j<1000;j++)
	            {             
                      vector[i].x[j] =0 ;
		      vector[i].y[j] = 0 ;
		    };      

     genetic(initial,hWnd,n);
      

     initial=1;
        
     for (i=0 ;i<10;i++)
       {
              for(j=0;j<1000;j++)
	            {             
		      vector[i].x[j] =0 ;
		      vector[i].y[j] =0 ;
		    };
       

        pas=0;
        Load (popcop,c,i,hWnd);                         
 
        L_init_var_ling(pvo,pvm,pvn,hWnd);
	Modific_var_ling (popcop,i,pvo,pvm,pvn,hWnd) ; // obtin noile valori ale tuturor var. ling.
      	/*for (k=0;k<6;k++)
         {
	  hDC =GetDC(hWnd);
	  f2=pvm[k].fCentroid;         
          nLength =sprintf(szBuffer," %d    %d   %d ",f2,pvm[k].fDispersieS,pvm[k].fDispersieD);
	  TextOut(hDC,400,20*k,szBuffer,nLength);
	  ReleaseDC(hWnd,hDC);
         };*/ 
	if (logic != 1)
           {
	      vector[i].x[0] = ri;
	      vector[i].y[0] = ti; 
           }
        else
	   {
	      vector[i].x[0] = xmem ;
	      vector[i].y[0] = ymem ;
	   } 
        rob =Sa_stie_si_rob(rob,vector,0,i,hWnd);
        moc=0;
	for(moc=0;moc<300;moc++)
	     {
           	       pas=pas+1;
		       Intermediar1(tip,obs,x1,y1,rob,TipVar1,TipVar2,vertical,hWnd,d);
		       com = c[tip[2]].b[tip[1]].a[tip[0]];
	               m= Com (com,hWnd);
		       Deplasare (rob,m,i,pas,x1,y1,vector,poz);
		       rob=  Sa_stie_si_rob(rob,vector,pas,i,hWnd);
		       f= CalculezFitnes (i,popcop,obs,rob,x1,y1);




		       if(     (rob.xCentru >= (x_final-15)) & (rob.yCentru >= (y_final-15)) & (rob.xCentru <= (x_final+15)) & ( rob.yCentru <=(y_final+15))  )//|| ( (rob.xCentru >= (x_final-15)) & (rob.yCentru <= (y_final+15)) ) || (  (rob.xCentru <= (x_final+15)) & (rob.yCentru >= (y_final-15))  )  ||  (  (rob.xCentru <= (x_final+15)) & (rob.yCentru <= (y_final+15)) ) )
	   	          {  
			      
                             goto Label;
                          };           
              };
   
		if  ( (rob.xCentru <(x_final-50) ) ||(rob.yCentru<(y_final-35))||(rob.xCentru >(x_final+50))||(rob.yCentru >(y_final+35)) )
                      {
			     popcop[i].Fitness = f +5000;
		       }
		else
		      {
                       Label:
                       popcop[i].Fitness =f;
		       }
			  
                              
	                        hDC =GetDC(hWnd);
                           
                                  nLength =sprintf(szBuffer," %lu       ",poppar[i].Fitness);
	                          TextOut(hDC,15*i,15*i,szBuffer,nLength);      
				  ReleaseDC(hWnd,hDC);   
                                
            };

        /* HERE YOU CAN MODIFY THE VALUE OF N */

	if (n >10000 )
	  {
	      hDC =GetDC(hWnd);
	      for (j=0;j<300;j++)
	           if( j !=0 )
	             {	          
	                if ((vector[rem].x[j] != 0)&(vector[rem].y[j] != 0) )
	                  { 
       	                    MoveTo(hDC, vector[0].x[j-1], vector[0].y[j-1]);
		            LineTo(hDC, vector[0].x[j], vector[0].y[j]);
	                   }
	             };
	       ReleaseDC(hWnd,hDC);
               goto Fight;


	   };	
        stop = 0;
	for (i1=0;i1<10;i1++)
         {
 	   if (popcop[i1].Fitness ==0)
 	     { 
	       Afiseaza_Drum(hWnd,obs,rob,i1,vector);
		 
	       rem=i1;
               stop=1;
	       goto Exit;
	    //   goto Fight;
	     };
	 
          };
       }

   while (  stop == 0);
   Exit:


   for (i=0;i<300;i++)
      if ( (vector[rem].x[i] ==0)&(vector[rem].y[i]==0) )
		mer =i; 



  
nr=0;
sin=0;
do {

   while(  PeekMessage(&msg, hWnd,WM_MOUSEFIRST,WM_MOUSELAST, PM_NOYIELD|PM_REMOVE) )
	    {
	      if (msg.message ==WM_LBUTTONDOWN)
		{
	      
			 sin =1;
		  
                 };
	      TranslateMessage(&msg);
              DispatchMessage(&msg);
	    };
   }
while (sin !=1);

do  {
      
	gettime(&t1);
	m11=60*t1.ti_min + t1.ti_sec;
	 
	do{
            gettime (&t2);
            m2=60*t2.ti_min +t2.ti_sec;


          }
	while (m2-m11<=2 );
                 
	  
		  
	while(  PeekMessage(&msg, hWnd,WM_MOUSEFIRST,WM_MOUSELAST, PM_NOYIELD|PM_REMOVE) )
	  {
	    if (msg.message ==WM_LBUTTONDOWN)
		{
                  
		  xMouse = LOWORD(msg.lParam);
		  yMouse = HIWORD(msg.lParam);
		  obs[con].xleft_up = xMouse-30;
                  obs[con].yleft_up = yMouse-30;
                  obs[con].xright_down = xMouse +30 ;
                  obs[con].yright_down = yMouse+30;
                  obs[con].xCentru = xMouse;
		  obs[con].yCentru = yMouse;
		  hDC =GetDC(hWnd);
		  Ellipse(hDC,obs[con].xleft_up , obs[con].yleft_up , obs[con].xright_down , obs[con].yright_down ) ;
		  ReleaseDC(hWnd,hDC);
		  con=con+1;
                       
                 };
	    TranslateMessage(&msg);
            DispatchMessage(&msg);
          };
	 nr =nr+1;
         rob =Sa_stie_si_rob(rob,vector,nr,rem,hWnd);

           
	 if ( test(obs,rob,x1,y1,d,con)==1 )
	     {
	       rob = Sa_stie_si_rob(rob,vector,nr-1,rem,hWnd);
	       hDC =GetDC(hWnd);      
               hpen = CreatePen(PS_SOLID|PS_INSIDEFRAME,1, RGB(255,255 , 255));
	       hpenOld = SelectObject(hDC,hpen);
               Ellipse(hDC,  rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down);
	       SelectObject(hDC, hpenOld);
	       DeleteObject(hpen);
	       ReleaseDC(hWnd,hDC);

               //    rob = Sa_stie_si_rob(rob,vector,nr,rem,hWnd);
	  
	       rob =Sa_stie_si_rob (rob,vector,nr,rem,hWnd);
	       hDC =GetDC(hWnd);
	       s1 = rob.xCentru;
               s2 = rob.yCentru;
	       rob.xleft_up = s1-20;
               rob.yleft_up = s2-20;
	       rob.xright_down = s1+20;
               rob.yright_down = s2+20;   
	  
              
	       Ellipse(hDC,  rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down);

	       for (j=0;j<300;j++)
	           if( j !=0 )
	             {	          
	                if ((vector[rem].x[j] != 0)&(vector[rem].y[j] != 0) )
	                  { 
       	                    MoveTo(hDC, vector[rem].x[j-1], vector[rem].y[j-1]);
		            LineTo(hDC, vector[rem].x[j], vector[rem].y[j]);
	                   }
	             };
	       ReleaseDC(hWnd,hDC);


                
	      }
         else
	     {




	       rob =  Sa_stie_si_rob(rob,vector,nr-1,rem,hWnd);
	       hDC =GetDC(hWnd);
               hpen = CreatePen(PS_SOLID|PS_INSIDEFRAME,1, RGB(255,255 , 255));
	       hpenOld = SelectObject(hDC,hpen);
               Ellipse(hDC,  rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down);
	       SelectObject(hDC, hpenOld);
	       DeleteObject(hpen);
	       ReleaseDC(hWnd,hDC);


               hDC =GetDC(hWnd);
               rob = Sa_stie_si_rob(rob,vector,nr-2,rem,hWnd);
               
	       s1 = rob.xCentru;
	       s2 = rob.yCentru;
	       xmem = s1;
               ymem = s2;
	       rob.xleft_up = s1-20;
               rob.yleft_up = s2-20;
	       rob.xright_down = s1+20;
               rob.yright_down = s2+20;   

	       Ellipse(hDC,  rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down);
	       for (i=0;i<30;i++)
		   Ellipse(hDC,obs[i].xleft_up , obs[i].yleft_up , obs[i].xright_down , obs[i].yright_down ) ;
	       ReleaseDC(hWnd,hDC);


	       hDC =GetDC(hWnd);

	       hpen = CreatePen(PS_SOLID|PS_INSIDEFRAME,1, RGB(255,255 , 255));
	       hpenOld = SelectObject(hDC,hpen);

		       	for (j=0;j<300;j++)
	                   if( j !=0 )
	                     {	          
	                       if ((vector[rem].x[j] != 0)&(vector[rem].y[j] != 0) )
	                          { 
       	                            MoveTo(hDC, vector[rem].x[j-1], vector[rem].y[j-1]);
		                    LineTo(hDC, vector[rem].x[j], vector[rem].y[j]);
	                          }
			    };
	       SelectObject(hDC, hpenOld);
	       DeleteObject(hpen);

	       
	       ReleaseDC(hWnd,hDC);

	       logic =1;

	       goto Reluare ;   
	      }
     } 
while ((rob.xCentru !=vector[rem].x[mer-1] )&(rob.yCentru!=vector[rem].y[mer-1] )  );


Fight:

       
   return 0;
}




VAR_LINGVISTICA* L_init_var_ling (pvo,pvm ,pvn,hWnd)
VAR_LINGVISTICA pvo[2];
VAR_LINGVISTICA pvm[6];
VAR_LINGVISTICA pvn[6];
HWND hWnd;
{

    int s;
    HDC hDC;
     short nLength;
   char szBuffer[100];
     int i;
  pvo[0].fCentroid =  20;
  pvo[0].fDispersieS = -2;
  pvo[0].fDispersieD = 42;
  pvo[0].fDispersieC = 0;

  pvo[1].fCentroid = 59;
  pvo[1].fDispersieS =37;
  pvo[1].fDispersieD = 81;
  pvo[1].fDispersieC = 0;      
  // pentru dx
 
  pvm[2].fCentroid  =  -118;     // -140;
  pvm[2].fDispersieS = -246;    // -290;
  pvm[2].fDispersieD =   10;    //     10;
  pvm[2].fDispersieC = 0  ;  //     0;
                           
  pvm[1].fCentroid  =  -354;    //  -420;
  pvm[1].fDispersieS = -482;    //  -570;
  pvm[1].fDispersieD = -226;     // -270;
  pvm[1].fDispersieC =  0  ;   //   0;

  pvm[0].fCentroid  =  -590;      //  -700;
  pvm[0].fDispersieS = -718;      //  -850;
  pvm[0].fDispersieD = -462;      //  -550;
  pvm[0].fDispersieC =  0  ;   //     0;
                            
  pvm[3].fCentroid  =  118  ;    //   140;
  pvm[3].fDispersieS = -10 ;    //    -10;
  pvm[3].fDispersieD = 246 ;    //    290;
  pvm[3].fDispersieC =  0  ;  //    0;

  pvm[4].fCentroid  = 354 ;	    //	 420;
  pvm[4].fDispersieS = 226 ;	    //	270;
  pvm[4].fDispersieD = 482 ;	     //	570;
  pvm[4].fDispersieC = 	0  ;   ///	0;

  pvm[5].fCentroid  = 590  ;     // 	700;
  pvm[5].fDispersieS = 462 ;	     //	550; 
  pvm[5].fDispersieD = 718 ;	    //	850;
  pvm[5].fDispersieC =	0  ;   //	 0;
   

  pvn[2].fCentroid  =  -75  ;	    //	  -90;
  pvn[2].fDispersieS = -164 ;	    //	-190;
  pvn[2].fDispersieD =  10    ;  //	10 ;
  pvn[2].fDispersieC =	0   ; //	 0;

  pvn[1].fCentroid  =  -225 ;	    //	 -270;
  pvn[1].fDispersieS = -314 ;	    //	-370;
  pvn[1].fDispersieD = -144 ;	    //	 -170;
  pvn[1].fDispersieC = 	0   ; //	0;

  pvn[0].fCentroid  =  -376 ;	    //	-450;
  pvn[0].fDispersieS = -450 ;	    //	-550;
  pvn[0].fDispersieD =	-294;    //	 -350;
  pvn[0].fDispersieC = 0    ;	    //	0;

  pvn[3].fCentroid  =  75   ;  //	90;
  pvn[3].fDispersieS = -10  ;	    //	-10;
  pvn[3].fDispersieD = 164  ;	   //	190;
  pvn[3].fDispersieC = 0     ;	    //	 0;

  pvn[4].fCentroid  =  225   ;	    //	270;
  pvn[4].fDispersieS = 144   ;	    //	 170;
  pvn[4].fDispersieD = 314  ;	    //	370;
  pvn[4].fDispersieC = 0    ;	    //	 0;

  pvn[5].fCentroid  =  376  ;	    //	450;
  pvn[5].fDispersieS = 294  ;	    //	 350; 
  pvn[5].fDispersieD = 450  ;	    //	550;
  pvn[5].fDispersieC = 0    ;	    //	0;



 return (pvo,pvm,pvn);
  };

FAR PASCAL Load_genetic_init(poppar)    
CROMOZOM poppar[10];
{
   int i,j,z;
   int k;
   int index1,index2;
   for (k=0;k<10;k++)
     {
      index1 = 0;
      index2 = 0;    
      for (z=0;z<2;z++)
       {
	for(i=0;i<6;i++) 
         {
          for(j=0;j<6;j++)     
          {
           if (z==0)
              {               
	        index1 =i*6 + j; 
                poppar[k].cromo[index1] = index1; 
              } 
            else  
              {
	        index2= 36+i*6+j;
                poppar[k].cromo[index2] = index2;
              }  
	   };
	 };
       };
       for (i=72 ;i< 114;i++)
         poppar[k].cromo[i] = 0;
     };

}
           
cod* FAR PASCAL LoadInitial (c)  
cod c[2];    
{   
  int i,j,z;
  int index1,index2; 
  for (z=0;z<2;z++)
   {
    for(i=0;i<6;i++) 
     {  
      for(j=0;j<6;j++) 
   
        {
          if (z==0)
            {               
              index1 =i*6 + j ;
              c[z].b[i].a[j]= index1; 
            } 
          else  
            {
              index2= 36+i*6+j ;
              c[z].b[i].a[j]  = index2;
            }  
	 };
       };
   };
return c;
}

int* FAR PASCAL Intermediar1(tip,obs,x1,y1,rob,TipVar1,TipVar2,vertical,hWnd,d)
int tip[3];
OBSTACOL obs[30];
int x1;
int y1;
ROBOT rob;
TIP_APARTENENTA TipVar1;
TIP_APARTENENTA TipVar2;
int vertical;
HWND hWnd;
unsigned long d;
{
     short nLength;
     char szBuffer[240] ;
     HDC hDC;
     int s;
     int b;
     TIP_APARTENENTA tipvar[30];
     int dx,dy;
     unsigned long d1;
     int timp;

  dx =x_final - rob.xCentru ;
  dy =y_final - rob.yCentru ;
  TipVar1 = Fuzificare (dx, pvm,6,hWnd);
  TipVar2 = Fuzificare (dy, pvn,6,hWnd);
  for (i=0; i< 30 ; i++)
    tipvar[i].iVarLingvistica = 1;        
  for (i=0; i < 30 ;i++)   
      {
   
     if (obs[i].xCentru != 0 )
      {	 
         d1 = sqrtl((obs[i].xCentru -rob.xCentru )*(obs[i].xCentru - rob.xCentru)   +(obs[i].yCentru-rob.yCentru)*(obs[i].yCentru-rob.yCentru));
   
         timp =d1;
         tipvar [i] = Fuzificare ( d1, pvo,2,hWnd);  
       }               
     else
         tipvar[i].iVarLingvistica = 1;	     
         
    
      };  
  vertical = 0;//  inseamna MARE = 0  adica robotul se deplaseaza cu viteza mare..high speed
  for (i=0;i<30;i++)
     if (tipvar[i].iVarLingvistica == 0  )
	  vertical = 1 ;  //inseamna MICA = 1  adica robotul se deplaseaza cu viteza mica ..low speed
	 tip[0]=TipVar1.iVarLingvistica;
	 tip[1]=TipVar2.iVarLingvistica;
         tip[2]=vertical;
   
    return tip;
}


TIP_APARTENENTA FAR PASCAL Fuzificare (  fInput,pvVar, nrvarling,hWnd)
int fInput;
VAR_LINGVISTICA pvVar[];
int nrvarling;
HWND hWnd;
{
   short nLength;
   char szBuffer[240] ;
   TIP_APARTENENTA  TipVar;
   HDC hDC;
   int s;
   float s1;
   int iNrVarLingvistice ;
   int   iContor=0;
   float miu1 =0;
   float miu2 =0;
   float d1=0;
   float d2=0;
   float c1=0;
   float c2=0;
   int S,D;
   int fI;
   int car;
   
   iNrVarLingvistice = nrvarling ;
   if (fInput< pvVar[0].fCentroid)
     {
       TipVar.iVarLingvistica  = 0;
       TipVar.fGradApartenenta = 1;
        goto Exit;
      } 
     else
       if (fInput > pvVar[iNrVarLingvistice -1].fCentroid)
         {
            TipVar.iVarLingvistica  =iNrVarLingvistice-1;
            TipVar.fGradApartenenta = 1;
            goto Exit; 
         }
         
   

   for (;;)
   {
      if((fInput < pvVar[iContor +1].fCentroid)||
         (iContor >= iNrVarLingvistice -1 )) break;
      iContor++;
   }
     c1 = pvVar[iContor].fCentroid;
     c2 = pvVar[iContor +1].fCentroid;


 
    if ((fInput <pvVar[iContor].fDispersieS)||(fInput >pvVar[iContor].fDispersieD))
           {
	      miu1 = 0;
	      TipVar.iVarLingvistica = iContor+1;
              goto Exit;
           }
    else
     {
	if(c1<0)   
          {
	     if (fInput <c1)
                  {
		     fI =fInput*(-1);
		     S = (-1)*pvVar[iContor].fDispersieS ;
                     car=(-1)*c1;
		     miu1=(S-fI)/(S-car);
		  }
	     else
                  {
		   if ((fInput >0)&(fInput>c1))
                     {
                       car=(-1)*c1;
		       D= pvVar[iContor].fDispersieD;
		       fI =fInput+car;
                       D=D+car;
		       miu1=(D-fI)/D;
                     }
		   else
                     {
		       if ((pvVar[iContor].fDispersieD <0)&(fInput >c1)&(fInput<0))
		         {
			    fI =fInput*(-1);
		            D = (-1)*pvVar[iContor].fDispersieD ;
                            car=(-1)*c1;
		            miu1=(fI-D)/(car-D);
                         }
		       else
                         {
		           if ((pvVar[iContor].fDispersieD >0)&(fInput<0)&(fInput>c1))
                               {
			          car=(-1)*c1;
		                  D= pvVar[iContor].fDispersieD;
		                  fI =(-1)*fInput+D;
                                  D=D+car;
		                  miu1=fI/D;
			       }
                          }
                      }
                  }

	   }
	else     
	   { 
	     if((fInput >c1)&(c1>0))
                {
                  D=pvVar[iContor].fDispersieD;
                  miu1=(D-fInput)/(D-c1);
                }
	     else
                {
		 if((fInput <0)&(c1>0))
                   {
                    S=(-1)*pvVar[iContor].fDispersieS+c1;
                    fI =(-1)*fInput+c1;
                    miu1=(S-fI)/S;
                   }
		 else
                   { 
                     if ((pvVar[iContor].fDispersieS>0)&(fInput>0)&((c1>0)&fInput<c1))
			  {
                           S=pvVar[iContor].fDispersieS;
                           miu1=(fInput-S)/(c1-S);
                          }
		     else
                          {
                           if ((fInput >0)&(pvVar[iContor].fDispersieS<0)&(fInput<c1)&(c1>0))
                             {
				S=(-1)*pvVar[iContor].fDispersieS;
                                fI =fInput+S;
				S=S+c1;
                                miu1=fI/S;
			     }
                           }
		   }
                }
	   }
      }
 
    if ((fInput <pvVar[iContor+1].fDispersieS)||(fInput >pvVar[iContor+1].fDispersieD))
	   {
              
	      miu2 = 0;
	      TipVar.iVarLingvistica = iContor;
              goto Exit;
           }
    else
      {
	 if(c2<0) 
	    {
	     if (fInput <c2)
                {
		     fI =fInput*(-1);
		     S = (-1)*pvVar[iContor+1].fDispersieS ;
                     car=(-1)*c2;
		     miu2=(S-fI)/(S-car);
		}
	     else
                {   
		   if (fInput >0)
                     {
                       car=(-1)*c2;
		       D= pvVar[iContor+1].fDispersieD;
		       fI =fInput+car;
                       D=D+car;
		       miu2=(D-fI)/D;
                     }
		   else
                     {
		       if (pvVar[iContor+1].fDispersieD <0)
		         {
			    fI =fInput*(-1);
		            D = (-1)*pvVar[iContor+1].fDispersieD ;
                            car=(-1)*c2;
		            miu2=(fI-D)/(car-D);
                         }
		       else
                         {
		           if ((pvVar[iContor+1].fDispersieD >0)&(fInput<0))
                               {
			          car=(-1)*c2;
		                  D= pvVar[iContor+1].fDispersieD;
		                  fI =(-1)*fInput+D;
                                  D=D+car;
		                  miu2=fI/D;
			       }
			  }
		      }
                 }
	    }
         else      
	   {
	     if(fInput >c2)
                {
                  D=pvVar[iContor+1].fDispersieD;
                  miu2=(D-fInput)/(D-c2);
                }
	     else
                {
		 if(fInput <0)
                   {
                    S=(-1)*pvVar[iContor+1].fDispersieS+c2;
                    fI =(-1)*fInput+c2;
                    miu2=(S-fI)/S;
                   }
		 else
                   { 
                     if (pvVar[iContor+1].fDispersieS>0)
			  {
                           S=pvVar[iContor+1].fDispersieS;
                           miu2=(fInput-S)/(c2-S);
                          }
		     else
                          {
                           if ((fInput >0)&(pvVar[iContor+1].fDispersieS<0))
                             {
				S=(-1)*pvVar[iContor+1].fDispersieS;
                                fI =fInput+S;
				S=S+c2;
                                miu2=fI/S;
			     }
                          }
		    }
                }
           }
      }


   if (miu2 >=miu1)
   {
     TipVar.iVarLingvistica = iContor +1 ;
     TipVar.fGradApartenenta = miu2;
   }
     else
       {
	  TipVar.iVarLingvistica = iContor;
          TipVar.fGradApartenenta = miu1;
	}
       Exit:
 return (TipVar);
     
}

Comanda FAR PASCAL Com ( com,hWnd )
int com;
HWND hWnd;
{
   Comanda m;
   short nLength;
   char szBuffer[240] ;
   HDC hDC;


  
  switch ( com )
     {
	case  0 :
		   m.dx =  -40;//-40;
		   m.dy =  -25;//-40;
                   break;
        case  1: 
                   m.dx =  -20;
		   m.dy =  -25;//-40;
                   break;
        case  2:
                   m.dx =  -10;
		   m.dy =  -25;//-40;
                   break;
        case  3 :  
                   m.dx =   10;
		   m.dy =  -25;//-40;
                   break;
        case 4 :
                   m.dx =   20;
		   m.dy =  -25;//-40;
                   break;
        case  5 :
                   m.dx =   40;
                   m.dy =  -25;//-40;
                   break;
        case  6 :   
                   m.dx =  -40;
		   m.dy =  -12;//-20;
                   break;
        case  7: 
                   m.dx =  -20;
		   m.dy =  -12;//-20;
                   break;
        case  8 :
                   m.dx =  -10;
		   m.dy =  -12;//-20;
                   break;
        case  9 :  
                   m.dx =   10;
		   m.dy =  -12;//-20;
                   break;
        case  10:  
                   m.dx =   20;
		   m.dy =  -12;//-20;
                   break;
        case  11 :
                   m.dx =   40;
		   m.dy =  -12;//-20;
                   break;
                   
	case  12 :
                   m.dx =  -40;
		   m.dy =  -6;//-10;
                   break;
        case  13: 
                   m.dx =  -20;
		   m.dy =  -6;//-10;
                   break;
        case  14 :
                   m.dx =  -10;
		   m.dy =  -6;//-10;
                   break;
        case  15:  
                   m.dx =   10;
		   m.dy =  -6;//-10;
                   break;
        case  16 : 
                   m.dx =   20;
		   m.dy =  -6;//-10;
                   break;
        case  17 :
                   m.dx =   40;
		   m.dy =  -6;//-10;
                   break;
                   
        case  18 :   
                   m.dx =  -40;
		   m.dy =  6;// 10;
                   break;
        case  19: 
                   m.dx =  -20;
		   m.dy =   6;//10;
                   break;
        case  20:
                   m.dx =  -10;
		   m.dy =   6;//10;
                   break;
        case  21:  
                   m.dx =  10;
		   m.dy =  6;// 10;
                   break;
        case  22 : 
                   m.dx =   20;
		   m.dy =   6;//10;
                   break;
        case  23:
                   m.dx =   40;
		   m.dy =   6;//10;
                   break;
                   
        case  24 :   
                   m.dx =  -40;
		   m.dy =   12;//20;
                   break; 
        case  25 : 
                   m.dx =  -20;
		   m.dy =  12;// 20;
                   break;
        case  26 :
                   m.dx =  -10;
		   m.dy =   12;//20;
                   break;
        case  27 : 
                   m.dx =   10;
		   m.dy =   12;//20;
                   break;
        case  28 :
                   m.dx =   20;
		   m.dy =   12;//20;
                   break;
        case 29 :
                   m.dx =   40;
		   m.dy =   12;//20;
                   break;
                   
        case  30:   
                   m.dx =  -40;
		   m.dy =   25;//40;
                   break;
        case  31: 
                   m.dx =  -20;
		   m.dy =   25;//40;
                   break;
        case  32:
                   m.dx =  -10;
		   m.dy =  25;// 40;
                   break;
        case  33:  
                   m.dx =   10;
		   m.dy =   25;//40;
                   break;
        case  34 :
                   m.dx =   20;
		   m.dy =   25;//40;
                   break;
        case  35:
                   m.dx =   40;
		   m.dy =   25;//40;
                   break;
                    
        case  36 :
                   m.dx =  -40;
		   m.dy =  -12;//-20;
                   break;
        case  37:
                   m.dx =  -20;
		   m.dy =  -12;//-20;
                   break;
        case  38:
                   m.dx =  -10;
		   m.dy =  -12;//-20;
                   break;  
        case  39:
                   m.dx =   10;
		   m.dy =  -12;//-20;
                   break;
        case  40:
                   m.dx =   20;
		   m.dy =  -12;//-20;
                   break;
        case  41:
                   m.dx =   40;
		   m.dy =  -12;//-20;
                   break;
                   
        case  42:    
                   m.dx =  -20;
		   m.dy =  -6;//-10;
                   break;
        case  43: 
                   m.dx =  -10;
		   m.dy =  -6;//-10;
                   break;
        case  44:     
                   m.dx =   -5;
		   m.dy =  -6;//-10;
                   break;
        case  45:  
                   m.dx =    5;
		   m.dy =  -6;//-10;
                   break;
        case  46: 
                   m.dx =   10;
		   m.dy =  -6;//-10;
                   break;
        case  47:
                   m.dx =   20;
		   m.dy =  -6;//-10;
                   break;
                   
        case  48 :   
                   m.dx =  -20;
		   m.dy =  -3;// -5;
                   break;
        case  49: 
                   m.dx =  -10;
		   m.dy =  -3; //-5;
                   break;
        case  50 :
                   m.dx =   -5;
		   m.dy =   -3;//-5;
                   break;
        case  51:  
                   m.dx =    5;
		   m.dy =   -3;//-5;
                   break;
        case 52: 
                   m.dx =   10;
		   m.dy =   -3;//-5;
                   break;
        case  53:
                   m.dx =   20;
		   m.dy =   -3;//-5;
                   break;
                   
        case  54 :   
                   m.dx =  -20;
		   m.dy =   3;// 5;
                   break;
        case  55: 
                   m.dx =  -10;
		   m.dy =   3;// 5;
                   break;
        case  56:
                   m.dx =   -5;
		   m.dy =   3;// 5;
                   break;
        case  57:  
                   m.dx =    5;
		   m.dy =   3;// 5;
                   break;
        case  58: 
                   m.dx =    10;
		   m.dy =    3;// 5;
                   break;
        case  59 :
                   m.dx =    20;
                   m.dy =   3; // 5;
                   break;
        case  60 :   
                   m.dx =   -20;
		   m.dy =   6;// 10;
                   break;
        case  61: 
                   m.dx =   -10;
		   m.dy =   6; //10;
                   break;
        case  62:
                   m.dx =    -5;
		   m.dy =   6;// 10;
                   break;
        case  63:  
                   m.dx =    5;
		   m.dy =   6;//10;
                   break;
	case  64:
                   m.dx =   10;
		   m.dy = 6 ;// 10;
                   break;
        case  65 :          
                   m.dx =   20;
		   m.dy =  6 ;//10;
                   break;
                   
        case  66 :   
                   m.dx =  -20;
		   m.dy =  12 ;//20;
                   break;
        case  67: 
                   m.dx =  -10;
		   m.dy =   12;//20;
		   break;
        case  68:
                   m.dx =  -5;
		   m.dy =  12;// 20;
                   break;
        case  69:  
                   m.dx =   5;
		   m.dy =  12;// 20;
                   break;
        case  70: 
                   m.dx =   10;
		   m.dy =  12; //20;
                   break;
       	case  71:
                   m.dx =   20;
		   m.dy =  12; //20;
		   break;       
         
      };

return (m);      
}                



CROMOZOM* FAR PASCAL genetic (initial,hWnd,n)
int initial;
HWND hWnd;
unsigned long n;
{
 short nLength;
 char szBuffer[240] ;
 int a,b;
 HDC hDC;
 int mocofan;
 if (initial ==1 )
   {               
     Combinare(popcop,poppar,hWnd); 
                            	   
     Ruleta(poppar,hWnd);
     Incrucisare(popcop,hWnd);
     Mutatie (n,popcop,hWnd);
			   

   }
 else
   {
    
     Ruleta(poppar,hWnd);     
    
     Incrucisare(popcop,hWnd);
     Mutatie (n,popcop,hWnd);                    

   }
   
   return (popcop,poppar);

}

CROMOZOM* FAR PASCAL Combinare (popcop,poppar,hWnd)
CROMOZOM  popcop[10];
CROMOZOM  poppar[10];
HWND hWnd;
{
  int i,j,s;
  CROMOZOM l;
  unsigned long cd;
  short nLength;
  char szBuffer[240] ;
  int a,b;
  HDC hDC;
  int li,m;


  for (i=0;i<10 ;i++)
	poptot[i] = popcop[i] ;

  for (i=10;i<20 ;i++)
	poptot[i] = poppar[i-10] ;
  j=0;
  for (i=0 ;i< 20;i++)       
    {
      for(s=j; s<20;s++)
        {
           if(poptot[j].Fitness > poptot[s].Fitness)
               {
                    l = poptot[s];
                    poptot[s] = poptot[j];
		    poptot[j] = l;
	       }
         };
      j=j+1;  
     };



   j=0;    
   for (i=0;i<10;i++)
    {
    for(j=0;j<114;j++)
      {
   	    poppar[i].cromo[j]=poptot[i].cromo[j];
    
   
      };
      cd=poptot[i].Fitness;
      poppar[i].Fitness=cd;
      
      
    };
       
		


  return poppar;
}


CROMOZOM*  FAR PASCAL Incrucisare (popcop,hWnd)
CROMOZOM popcop[10] ;
HWND hWnd;
{

short nLength;
char szBuffer[240] ;
  
  HDC hDC;
int i,j,m,k,s;
int t=0;
int incr[50];
int set=0;
int a;
struct time toc;
j=0;

for (i=0;i<50;i++)
 incr[i]=0;
while (t==0)
{
  gettime(&toc);
  k = random (113);
  a = 0;
  for (i=0;i < 50 ;i++)
    {
	  if ((incr[i] == 0) & (incr[i-1] != 0) &  ( i-1 >= 0))
             {
                j=i+1;
	     };
        
    };
  for(i=0;i<50; i++)
    a=a+incr[i];
  if (j==0)
       m = 50 -1 ;
  else
       m=  50-j;
  if ((a+k+m+1) < 114)
    {
     if(j==0)
       incr[0]=k+1;
     else   
        incr[j-1] = k+1;
     };
  if (incr[49] != 0)
    {
      t=1;
    };
};


for ( i = 0;i < 10; i=i+2)
    {
       for (j =0 ; j < 50 ; j++)
          {
             t= 0;
             for ( s =0; s< j; s++)
                {
                   t=t+incr [s];
                };
            if ((j%2)== 0 ) 
                {
                   k = incr[j];
                   for (m=t;m<k+t;m++)
                     {
                         popcop[i].cromo[m] = popcop[i].cromo[m];
                         popcop[i+1].cromo[m] = popcop[i+1].cromo[m];
                     };
                }
             else                   
                {
                  k=incr[j];
                  for (m=t;m<k+t;m++)
                     {
                       popcop[i].cromo[m]= popcop[i+1].cromo[m] ;
		       popcop[i+1].cromo[m]= popcop[i].cromo[m] ;
                     };
                 };
 	   };
    };           
  return popcop ;
}
   
/* A MORE INTERESTING CROSSOVER FUNCTION BUT THIS FUNCTION DELAY THE PROGRAM SPEED ----MAY BE
   THIS FUNCTION IS CAPABLE TO RESOLVE VERY BAD SITUATION WHICH NORMALY CAN'T BE RESOLVED
   BY THE OTHER FUNCTION OF CROSSOVER FROM ABOVE
  */
/*
CROMOZOM*  FAR PASCAL Incrucisare (popcop,hWnd)
CROMOZOM popcop[10] ;
HWND hWnd;
{
short nLength;
char szBuffer[240] ;  
HDC hDC;
int i,j,m,k,s,pr;
int t=0;
int  incr[113];  
int set=0;
int a,lol,sort;
int mut;
int x,y,k1,t1,t2,n;
int pas,pasul,pasi,pasit,ti;
int crim[10];
struct time toc;
j=0;
pasul=0;
crim[0]=random(10);

do
  {
    ti=0;
    pas =random(10);
    for (i=0;i<=pasul;i++)
      if (crim[i] == pas)
      	{
         ti=1;
        };
    if (ti != 1)
     {
       pasul =pasul+1;
       crim[pasul] = pas;
     
     };

   }
while (pasul <9);
  



for(pr=0;pr<10;pr=pr+2)
{
  gettime(&toc);
  mut = random(112);//53+toc.ti_sec);
  mut =mut+1;   //inlocuiesc pe 20 cu mut
  j=0; 
  t=0;
  for (i=0;i<mut;i++)
    incr[i]=0;
  while (t==0)
   {
    gettime(&toc);
    k = random (112);//53+toc.ti_sec);
    a = 0;
    for (i=0;i <mut  ;i++)
      {
 
          if ((incr[i] == 0) & (incr[i-1] != 0) &  ( i-1 >= 0))
             {
                j=i+1;
	     };
        
      };
    for(i=0;i<mut; i++)
       a=a+incr[i];
    if (j==0)
         m = mut -1 ;
    else
         m=  mut -j;
    if ((a+k+m+1) < 114)
      {
       if(j==0)
         incr[0]=k+1;
       else   
         incr[j-1] = k+1;
       };
    if (incr[mut-1] != 0)
      {
        t=1;            
       };
      
   };
     k=0;
     t=0;
     pasi = crim[pr];
     pasit = crim[pr+1];

 
     for (j =0 ; j <mut  ; j++)
          {
             t= 0;
             for ( s =0; s< j; s++)
                {
                   t=t+incr [s];
		};
	 
            if ((j%2)== 0 ) 
               {
                   k = incr[j];
                   for (m=t;m<k+t;m++)
                     {
                         popcop[pasi].cromo[m] = poppar[pasi].cromo[m];
                         popcop[pasit].cromo[m] = poppar[pasit].cromo[m];
                     };
		}
             else                   
                {
                  k=incr[j];
                  for (m=t;m<k+t;m++)
                     {
		       popcop[pasi].cromo[m]= popcop[pasit].cromo[m] ;
		       popcop[pasit].cromo[m]= popcop[pasi].cromo[m] ;
                     };
                 };
	   }; 


    };

   return popcop ;

} 
   
*/


CROMOZOM*  FAR PASCAL Ruleta (poppar,hWnd)
CROMOZOM poppar[10];
HWND hWnd;
{
   short nLength;
   char szBuffer[240] ;
   int a,b;
   HDC hDC;
   struct time tot;
   inter  fit[10] ;
   int i,sort,k;
   int lovit2,total,unitate,j;
   int rest,mocofan;
   int s;
   ldiv_t x[10];
	     
   for (i=0;i<10 ;i++)              ////era cu o mie acum e cu 100
     {
       fit[i].l = poppar[i] ;
       fit[i].m = poppar[i].Fitness/1000 ; //am fitnesul  de forma 12000 1000 50000 ..obtin fitnes de forma 1 12 50
       fit[i].m = 1000 / fit[i].m ; // obtin in ordine descrescatoare ....100/1  100/12 ...primul fiind cromozomul cu fitnesul cel mai mic deci cel mai bun cromozom
                   
     };
   total=0;
   for (i=0 ;i<10;i++)
    total = total + fit[i].m ;  // calculez totalul lui 100/1 + 100/12....     otin X 
 
   unitate = total /100 ;  //impart pe total adica X la 100 
   rest =total%100;
   if (rest>50)
      unitate =unitate+1;
   for (i=0 ; i<10 ;i++)
      {
        x[i]=ldiv(fit[i].m,unitate);
     
      };
  for (i=0;i<10;i++)
     if (x[i].quot <1)
        {
	 if ( (x[i].quot+ x[i].rem*10) >= 1)
		fit[i].m =x[i].quot+ x[i].rem *10;
	 else
	    if(   ( (x[i].quot+ x[i].rem*10) < 1 ) & ( (x[i].quot+ x[i].rem*100) >= 1 )  )
		fit[i].m =  x[i].quot+ x[i].rem*100;
	    else
	       if (    ( (x[i].quot+ x[i].rem*10) < 1 ) & ( (x[i].quot+ x[i].rem*100) < 1 ) &  ( (x[i].quot+ x[i].rem*1000) >= 1 )   )
	      	  fit[i].m =  x[i].quot+ x[i].rem*1000;
               else
                  fit[i].m = 3; 
         }
     else
       	fit[i].m=x[i].quot;

      

   for (i=0;i<10;i++)                                      //    acum chiar construiesc discul
    for (j=1;j<=fit[i].m;j++)                             //    obs[0].ob[1] =1

     {                                                   //    obs[0].ob[1] =2
       if (i == 0)                                       //    obs[0].ob[2] =3
	 obst[i].ob[j] = j;                               //    ................
       else
        {                                             //    obs[1].ob[1] = obs[0].ob[2] +1
	 if ((i != 0) &(j ==1))
	   {
	                                                 //    obs[1].ob[2] = obs[1].ob[1] +1
	     obst[i].ob[1] = obst[i-1].ob[fit[i-1].m] + 1;   //
	    }
	 else
	    {                                                  //
	       obst[i].ob[j] = obst[i].ob[j-1] + 1;            //


	     }
         }
     };
        

  total1=0;
  for (i=0;i<10;i++)
     {   
          total1 =total1+ fit[i].m ;
      };
      
   
  for( i=0;i<10;i++ )
   {
    lovit2=0;
    lovit2 =random (total1);
    lovit2=lovit2+1;

          

   for(s=0;s<10;s++) 
    for (j=1 ;j< fit[s].m ;j++)     
      if (obst[s].ob[j] == lovit2)
       {   
	   popcop[i] = poppar[s];  
       
        };
   };
       
  
      for(i=0;i<10;i++)
   	     popcop[i].Fitness =0;
   
  return popcop ;
}


CROMOZOM* FAR PASCAL Mutatie(n,popcop,hWnd)
unsigned long n;
CROMOZOM popcop[10];
HWND hWnd;
{
  short nLength;
  char szBuffer[240] ;
  int a,b;
  HDC hDC;
  int i,j,in_loc,lovit;
  struct time toc,toc1; 
    if ((n%1)==0 )
     {

        hDC =GetDC(hWnd);
  	
        nLength =sprintf(szBuffer," %d  ",n);
	TextOut(hDC,700,5,szBuffer,nLength);

	ReleaseDC(hWnd,hDC);
        for (i=0;i<10;i++)   
	  {
           for (j=0;j<114;j++)   
	     {
        
		
	   //	   gettime(&toc);                   
		   lovit = random (114);//55 +toc.ti_sec);   // 114
		   if (j == lovit )   
		     {
	   //	       gettime(&toc1);


		       in_loc = random(72);//13 +toc1.ti_sec) ;// 72

		       popcop[i].cromo[j] = in_loc ; 
		     
       		     };
             };
	 };
	 	
     };   
    return popcop;
}




traiectorie* FAR PASCAL Deplasare (rob,m,i,pas,x1,y1,vector,poz)
ROBOT rob;
Comanda m;
int i;
int pas;
int x1;
int y1;
traiectorie vector[10];
int poz;
{
    int x,y,z,j;
    if(pas==0)
      { 
        rob.xCentru =ri ;
	rob.yCentru =ti ;
        vector[i].x[pas] = rob.xCentru ;
        vector[i].y[pas] = rob.yCentru ;

       }
   else
       {
        vector[i].x[pas]=vector[i].x[pas-1] +m.dx;
        vector[i].y[pas]=vector[i].y[pas-1] +m.dy;

       }

 return vector;  
}




FAR PASCAL Afiseaza_Drum (hWnd,obs,rob,i,vector)
HWND hWnd;
OBSTACOL obs[30];
ROBOT rob;
int i;
traiectorie vector[10];
{
   
     int ic,j;
     short nLength;
     char szBuffer[100];
     HDC hDC;
     hDC = GetDC(hWnd);
 

     MoveTo(hDC,10,25);
     LineTo(hDC,10,480);
     LineTo(hDC,750,480);
     LineTo(hDC,750,25);   
     LineTo(hDC,10,25);
     nLength = sprintf(szBuffer,"Terrain Map 3 ");
     TextOut (hDC,352,5,szBuffer,nLength);



    
      

      	obs[0].xleft_up = 190;
        obs[0].yleft_up = 110;
        obs[0].xright_down =250; 
        obs[0].yright_down =170; 
        obs[0].xCentru = 220;
        obs[0].yCentru = 140;
        
 
        obs[1].xleft_up =400;	
        obs[1].yleft_up =210; 
        obs[1].xright_down =460; 
        obs[1].yright_down =270; 
        obs[1].xCentru = 430;
        obs[1].yCentru = 240;
        
         
        obs[2].xleft_up =40;	
        obs[2].yleft_up =216; 
        obs[2].xright_down =100; 
        obs[2].yright_down =276; 
        obs[2].xCentru = 70;
	obs[2].yCentru = 246;
        
      
        obs[3].xleft_up =40;	
        obs[3].yleft_up =370; 
        obs[3].xright_down =100; 
        obs[3].yright_down =430; 
        obs[3].xCentru = 70;
        obs[3].yCentru = 400;
        
        obs[4].xleft_up =150;	
        obs[4].yleft_up =330; 
        obs[4].xright_down =210; 
        obs[4].yright_down =390; 
        obs[4].xCentru = 180;
        obs[4].yCentru = 360;
        
        obs[5].xleft_up =530;	
        obs[5].yleft_up =140; 
        obs[5].xright_down =590; 
        obs[5].yright_down =200; 
        obs[5].xCentru = 560;
        obs[5].yCentru = 170 ;
         
        obs[6].xleft_up =610;	
        obs[6].yleft_up =210; 
        obs[6].xright_down =670; 
        obs[6].yright_down =270;
        obs[6].xCentru = 640;
	obs[6].yCentru = 240;
         
      
        obs[7].xleft_up =445;	
        obs[7].yleft_up =130;
        obs[7].xright_down =505; 
        obs[7].yright_down =190;
        obs[7].xCentru = 475;
        obs[7].yCentru = 160;  
        
	obs[8].xleft_up =429;
        obs[8].yleft_up =396; 
        obs[8].xright_down =489; 
        obs[8].yright_down =456; 
        obs[8].xCentru = 459;
        obs[8].yCentru = 426;
        
        obs[9].xleft_up =510;	
        obs[9].yleft_up =250; 
        obs[9].xright_down =570; 
        obs[9].yright_down =310; 
        obs[9].xCentru = 540;
	obs[9].yCentru =280;


	obs[10].xleft_up =  110;
        obs[10].yleft_up =  130;
	obs[10].xright_down = 170; 
	obs[10].yright_down = 190; 
        obs[10].xCentru =  140; 
        obs[10].yCentru =  160; 



      

        
        for (ic=0;ic<30;ic++) 
	  Ellipse(hDC,obs[ic].xleft_up , obs[ic].yleft_up , obs[ic].xright_down , obs[ic].yright_down ) ;

	for (j=0;j<300;j++)
	 if( j !=0 )
	   {
	   
	    if ((vector[i].x[j] != 0)&(vector[i].y[j] != 0) )
	      { 
       	        MoveTo(hDC, vector[i].x[j-1], vector[i].y[j-1]);
		LineTo(hDC, vector[i].x[j], vector[i].y[j]);
	      }
	   };

	ReleaseDC (hWnd,hDC );
	return 1;
}  


unsigned long FAR PASCAL CalculezFitnes(i,popcop,obs,rob,x1,y1)
int i;
CROMOZOM popcop[];
OBSTACOL obs[30];
ROBOT rob;
int x1;
int y1;
{


       if (test(obs,rob,x1,y1,d,con) == -1)
           popcop[i].Fitness = popcop[i].Fitness +1000 ;  //1000 //cu 2000 merge cand robotul este sus // cu 1000 merge cand este jos
       if (test1(rob)==-1)
	   popcop[i].Fitness = popcop[i].Fitness+ 1000;  //2000
  

       return (popcop[i].Fitness);
}



int FAR PASCAL test ( obs, rob,x1,y1,d,con )
OBSTACOL obs[30];
ROBOT rob;
int x1;
int y1;
unsigned long d;
int con;
{
 int m,i;
 int t=1;

 for (i=0;i<con;i++)       
   {

     d = sqrtl((obs[i].xCentru - rob.xCentru)*( obs[i].xCentru - rob.xCentru) + ( obs[i].yCentru - rob.yCentru)*( obs[i].yCentru - rob.yCentru) );
 
     if (d < 50) 
      {
        m= i;
        t= -1;// hit an obstacle
      };                
    };
 if (t <0  )
   return (-1);
 else
   return  (+1);  
  
}  
          


unsigned long FAR PASCAL CalculezFitnes1(i,poppar,obs,rob,x1,y1)
int i;
CROMOZOM poppar[];
OBSTACOL obs[30];
ROBOT rob;
int x1;
int y1;
{


       if (test(obs,rob,x1,y1,d,con) == -1)
	 
	   poppar[i].Fitness = poppar[i].Fitness +1000 ;//1000  // 2000
       if (test1(rob)==-1)
           poppar[i].Fitness = poppar[i].Fitness+ 1000; //3000  //3000
   

       return (poppar[i].Fitness);
}



ROBOT FAR PASCAL Sa_stie_si_rob(rob,vector,pas,i,hWnd)
ROBOT rob;
traiectorie vector[10];
int pas;
int i;
HWND hWnd;
{
     int s,s1;
     rob.xCentru =  vector[i].x[pas];      

     rob.yCentru = vector[i].y[pas];
   
 return rob;
}



int FAR PASCAL test1(rob)
ROBOT rob;
{
 int dist1,dist2,dist3,dist4;


   dist1 = 760 -rob.xCentru;  //760
   if(dist1 <=20)
      return -1;
   dist2 = rob.xCentru -10;
   if(abs(dist2) <=20)
      return -1;   
   dist3 = rob.yCentru- 25;
   if (dist3 <=20)
      return -1;
   dist4 = 505 -rob.yCentru;   //505
   if (dist4 <=20)
      return -1;
   if( (dist1>20)&(dist2>20)&(dist3>20)&(dist4>20) )
      return 0;


}


cod* FAR PASCAL Load(popcop,c,i,hWnd)
CROMOZOM popcop[];
cod c[2];
int i;
HWND hWnd;
{

  int s,k;

  int j,z;
  int index1,index2; 
  for (z=0;z<2;z++)
    for(k=0;k<6;k++)  
      for(j=0;j<6;j++) 
   
       {
        if (z==0)
          {               
            index1 =k*6 + j; 
            c[z].b[k].a[j] =popcop[i].cromo[index1]; 
          }    
        else  
          {
            index2= 36+k*6+j; 
            c[z].b[k].a[j] =popcop[i].cromo[index2];
          }   
       };
   return c;
}
 


VAR_LINGVISTICA* FAR PASCAL Modific_var_ling (popcop,t,pvo,pvm,pvn,hWnd)
CROMOZOM popcop[];
int t;
VAR_LINGVISTICA pvo[2];
VAR_LINGVISTICA pvm[6];
VAR_LINGVISTICA pvn[6];
HWND hWnd;
{
     short nLength;
     char szBuffer[240] ;
     HDC hDC;

   int temp;
   div_t x;
   int i,k ;
   int r,c ;
   int contor1,contor2,contor3 ;
   contor1 = 0;
   contor2 = 0;
   contor3 = 0; 
   for (i=72;i<114; i++)
     {
      if (i < 90)  
          {
             k= i-72;
             c= k / 3 ;
	     r= k % 3;
	     if ((c != 0) &  (r ==0))
                contor1 = contor1 +1 ;
	     if (r == 0)
              {
		    temp = popcop[t].cromo[72 +c*3 +0]; 
		    temp = temp +1;                 
		    x = div (temp, 4);          
		    if (x.rem > 0.5)              
                       temp = x.quot + 1;
		    else
		       temp = x.quot ;
		    if ( temp < 10 )
		       temp = (-1)*temp ;
		    else
                       temp = 19-temp; 
		    pvm[contor1].fDispersieS = temp + pvm[contor1].fDispersieS;
               };
	     if (r == 1)
		 {
	            temp = popcop[t].cromo[72 +c*3 +1]; 
		    temp = temp +1;                 
		    x = div (temp, 4);           
		    if (x.rem > 0.5)               
                       temp = x.quot + 1;
		    else
		       temp = x.quot ;
		    if ( temp < 10 )
		       temp = (-1)*temp ;
		    else
                       temp =19-temp; 
		    pvm[contor1].fDispersieC = temp ;
		    pvm[contor1].fCentroid = pvm[contor1].fCentroid  + pvm[contor1].fDispersieC ;
		    
		 };
	     if (r == 2)
		 {
		  temp = popcop[t].cromo[72 +c*3 +2];
		    temp = temp +1;                
		    x = div (temp, 4);            
		    if (x.rem > 0.5)               
                       temp = x.quot + 1;
		    else
		       temp = x.quot ;
		    if ( temp < 10 )
		       temp = (-1)*temp ;
		    else
                       temp =19-temp;
		    pvm[contor1].fDispersieD = temp + pvm[contor1].fDispersieD; 

		   };
        };
      if ((i >= 90) && (i < 108))
	  {
             k = i-90 ;
             c = k / 3 ;
	     r = k % 3;
	     if ((c != 0) & (r ==0))
                contor2 = contor2 +1 ;
	     if (r == 0)
                { 
		    temp = popcop[t].cromo[90 +c*3 +0]; 
		    temp = temp +1;                 
		    x = div (temp, 4);            
		    if (x.rem > 0.5)               
                       temp = x.quot + 1;
		    else
		       temp = x.quot ;
		    if ( temp < 10 )
		       temp = (-1)*temp ;
		    else
                       temp =19-temp;
		    pvn[contor2].fDispersieS = temp + pvn[contor2].fDispersieS; 
		};
	     if (r == 1)
		{
		    temp = popcop[t].cromo[90 +c*3 +1]; 
		    temp = temp +1;                
		    x = div (temp, 4);            
		    if (x.rem > 0.5)               
                       temp = x.quot + 1;
		    else
		       temp = x.quot ;
		    if ( temp < 10 )
		       temp = (-1)*temp ;
		    else
                       temp = 19-temp;
		    pvn[contor2].fDispersieC = temp + pvn[contor2].fDispersieC;
		    pvn[contor2].fCentroid  = pvn[contor2].fCentroid + pvn[contor2].fDispersieC ;
		};

	     if (r == 2)
		{
		    temp = popcop[t].cromo[90 +c*3 +2]; 
		    temp = temp +1;                 
		    x = div (temp, 4);            
		    if (x.rem > 0.5)              
                       temp = x.quot + 1;
		    else
		       temp = x.quot ;
		    if ( temp < 10 )
		       temp = (-1)*temp ;
		    else
                       temp = 19-temp;
		    pvn[contor2].fDispersieD = temp + pvn[contor2].fDispersieD;
		};
	   }; 
       if (i >= 108)
          {
             k = i-108 ;
             c = k / 3 ;
	     r = k % 3;
	     if ((c != 0) & (r ==0))
                contor3 = contor3 +1 ;
	     if (r == 0)
		{
		    temp = popcop[t].cromo[108 +c*3 +0]; 
		    temp = temp +1;                 
		    x = div (temp,18 );            
		    if (x.rem > 0.5)              
                       temp = x.quot + 1;
		    else
		       temp = x.quot ;
		    if ( temp < 3 )
		       temp = (-1)*temp ;
		    else
                       temp = 5-temp;
		    pvo[contor3].fDispersieS = temp + pvo[contor3].fDispersieS;
		};
	     if (r == 1)
		{
		    temp = popcop[t].cromo[108 +c*3 +1]; 
		    temp = temp +1;                 
		    x = div (temp, 18);            
		    if (x.rem > 0.5)              
                       temp = x.quot + 1;
		    else
		       temp = x.quot ;
		    if ( temp < 3 )
		       temp = (-1)*temp ;
		    else
                       temp = 5-temp;
		    pvo[contor3].fDispersieC = temp + pvo[contor3].fDispersieC;
		    pvo[contor3].fCentroid  = pvo[contor3].fCentroid + pvo[contor3].fDispersieC ;
		 };
	     if (r == 2)
                {
		    temp = popcop[t].cromo[108 +c*3 +2]; 
		    temp = temp +1;                 
		    x = div (temp, 18);            
		    if (x.rem > 0.5)              
                       temp = x.quot + 1;
		    else
		       temp = x.quot ;
		    if ( temp < 3 )
		       temp = (-1)*temp ;
		    else
                       temp =5-temp;
		    pvo[contor3].fDispersieD = temp + pvo[contor3].fDispersieD;
		 };       	   
	   };
     };
    return (pvm,pvn,pvo) ;    
   
}


float  FAR PASCAL Go2 (rob,hWnd,vector,popcop,poppar,lParam,wParam)
ROBOT rob;
HWND hWnd;
traiectorie vector[10];
CROMOZOM popcop[10];
CROMOZOM poppar[10];
LPARAM lParam;
WPARAM wParam;
{
   short nLength;
   int z;
   char szBuffer[100];
   HDC hDC;
   Comanda m;
   int i,j,i1;
   int stop,moc;
   int s,s1,s2,sin;
   int top[3];
   int l1,m1,n1,k;
   unsigned long f1,f;
   MSG msg;
   int f2;
   struct time t1,t2;
   unsigned long  m11,m2;
   int xMouse,yMouse;
   PAINTSTRUCT ps;
   POINT pon;
   HPEN  hpen,hpenOld ; 
   int ionut,camelia;
   int tut=0;



do {
     if (tut <1)
       {
  	   while(  PeekMessage(&msg, hWnd,WM_MOUSEFIRST,WM_MOUSELAST, PM_NOYIELD|PM_REMOVE) )
	    {
	      if (msg.message ==WM_LBUTTONDOWN)
		{
                  
		  xMouse = LOWORD(msg.lParam);
		  yMouse = HIWORD(msg.lParam);
		  ri = xMouse;
                  ti = yMouse;
		  rob.xleft_up = xMouse-20;
                  rob.yleft_up = yMouse-20;
                  rob.xright_down = xMouse +20;
                  rob.yright_down = yMouse +20;
                  rob.xCentru = xMouse;
		  rob.yCentru = yMouse;
		  hDC =GetDC(hWnd);
		  Ellipse(hDC,rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down ) ;
		  ReleaseDC(hWnd,hDC);   
                  tut=1;     
                 };
	      TranslateMessage(&msg);
              DispatchMessage(&msg);
            };
	}
      else
        {
	    while(  PeekMessage(&msg, hWnd,WM_MOUSEFIRST,WM_MOUSELAST, PM_NOYIELD|PM_REMOVE) )
	     {
	        if (msg.message ==WM_LBUTTONDOWN)
		  {
                  
		     x_final = LOWORD(msg.lParam);
		     y_final = HIWORD(msg.lParam);
		   
		     hDC =GetDC(hWnd);
		     SetPixel(hDC,x_final,y_final,RGB(0,0,0) );
		     ReleaseDC(hWnd,hDC);
               
	      
                     tut=2;     
                  };
	        TranslateMessage(&msg);
                DispatchMessage(&msg);
            };
         }



}
while (tut < 2);


   Reluare :    
   n=0;
   for (i=0;i<10;i++)
      {
       poppar[i].Fitness = 0;
       popcop[i].Fitness = 0 ;
      };
   L_init_var_ling(pvo,pvm,pvn,hWnd);
   Load_genetic_init(poppar);
   LoadInitial(c);  
   for(i=0;i<10;i++)
     poppar[i].Fitness =0;
   pas =0;
     for(i=0;i<10 ;i++)
       {
         for(j=0;j<300;j++)
           { 
   	  if(j==0)
	    {
	     if(logic != 1)
              {
	      vector[i].x[0] =ri; 
	      vector[i].y[0] =ti;
	      }
	     else
	      {
	      vector[i].x[0] = xmem;
	      vector[j].y[0] = ymem; 
	       }
	    }
 	   else
  	    {
	      vector[i].x[j] = 0;
	      vector[i].y[j] = 0;
             }
           };
        };
    Sa_stie_si_rob(rob,vector,pas,0,hWnd);
    pas =1;
    ionut = 0;


    do
     {
	  
	   Intermediar1(tip,obs,x1,y1,rob,TipVar1,TipVar2,vertical,hWnd,d);

	  

           com = c[tip[2]].b[tip[1]].a[tip[0]];
    	   m= Com (com,hWnd); 
 
           Deplasare (rob,m,0,pas,x1,y1,vector,poz);
	 
	   rob=  Sa_stie_si_rob(rob,vector,pas,0,hWnd);

	   f1= CalculezFitnes1 (0,poppar,obs,rob,x1,y1);
	   pas=pas+1;   


//1
	if (     (ri >= x_final)&(ti <= y_final)&( rob.xCentru <= (x_final+10) )&( rob.yCentru >= (y_final-6) ) )
	           ionut =1;     
//2
	if (     (ri >= x_final)&(ti >= y_final)&( rob.xCentru <= (x_final+15) )&( rob.yCentru <= (y_final+15) ) )
		   ionut =1;
//0		        
	if (     (ri <= x_final)&(ti <= y_final)&( rob.xCentru >= (x_final-10) )&( rob.yCentru >= (y_final-6) ) )
		   ionut =1;
//3		        
	if (     (ri <= x_final)&(ti >= y_final)&( rob.xCentru >= (x_final-15) )&( rob.yCentru <= (y_final+15) ) )
	           ionut =1;     


      }
   while (ionut != 1);
   for (i=0;i<10;i++)
          poppar[i].Fitness = f1 ;
    if (poppar[0].Fitness ==0)
      {
	
		Afiseaza_Drum2(hWnd,obs,rob,0,vector);
           //     goto Fight;
   	   	goto Exit;
      };
     
     
	          
    n=0;
    initial =0;
    
   do {
             n=n+1;
	     for(i=0;i<10;i++)
	         for(j=0;j<1000;j++)
	            {             
                      vector[i].x[j] =0 ;
		      vector[i].y[j] = 0 ;
		    };      

       genetic(initial,hWnd,n);  

       initial=1;   
       for (i=0 ;i<10;i++)
        {
              for(j=0;j<1000;j++)
	            {             
		      vector[i].x[j] =0 ;
		      vector[i].y[j] =0 ;
		    };
       

        pas=0;
        Load (popcop,c,i,hWnd);                         
 
        L_init_var_ling(pvo,pvm,pvn,hWnd);
	Modific_var_ling (popcop,i,pvo,pvm,pvn,hWnd) ; 
	
	if (logic != 1)
           {
	      vector[i].x[0] = ri;
	      vector[i].y[0] = ti; 
           }
        else
	   {
	      vector[i].x[0] = xmem ;
	      vector[i].y[0] = ymem ;
	   } 
        rob =Sa_stie_si_rob(rob,vector,0,i,hWnd);
        moc=0;
	for(moc=0;moc<300;moc++)
	     {
           	       pas=pas+1;
		       Intermediar1(tip,obs,x1,y1,rob,TipVar1,TipVar2,vertical,hWnd,d);
		       com = c[tip[2]].b[tip[1]].a[tip[0]];
	               m= Com (com,hWnd);
		       Deplasare (rob,m,i,pas,x1,y1,vector,poz);
		       rob=  Sa_stie_si_rob(rob,vector,pas,i,hWnd);
		       f= CalculezFitnes (i,popcop,obs,rob,x1,y1);




		       if(     (rob.xCentru >= (x_final-15)) & (rob.yCentru >= (y_final-15)) & (rob.xCentru <= (x_final+15)) & ( rob.yCentru <=(y_final+15))  )//|| ( (rob.xCentru >= (x_final-15)) & (rob.yCentru <= (y_final+15)) ) || (  (rob.xCentru <= (x_final+15)) & (rob.yCentru >= (y_final-15))  )  ||  (  (rob.xCentru <= (x_final+15)) & (rob.yCentru <= (y_final+15)) ) )
	   	          {  
			      
                             goto Label;
                          };           
              };
   
		if  ( (rob.xCentru <(x_final-50) ) ||(rob.yCentru<(y_final-35))||(rob.xCentru >(x_final+50))||(rob.yCentru >(y_final+35)) )
                      {
			     popcop[i].Fitness = f +5000 ;
		       }
		else
		      {
                       Label:
                       popcop[i].Fitness =f;
		       }
			  
                           
	                    /*    hDC =GetDC(hWnd);
                           
                                  nLength =sprintf(szBuffer," %lu       ",poppar[i].Fitness);
	                          TextOut(hDC,15*i,15*i,szBuffer,nLength);      
				  ReleaseDC(hWnd,hDC);   
                             */  
            };

      /* HERE YOU CAN MODIFY THE VALUE OF N */
	     	
      if (n >10000 )
	  {
	      hDC =GetDC(hWnd);
	      for (j=0;j<300;j++)
	           if( j !=0 )
	             {	          
	                if ((vector[rem].x[j] != 0)&(vector[rem].y[j] != 0) )
	                  { 
       	                    MoveTo(hDC, vector[0].x[j-1], vector[0].y[j-1]);
		            LineTo(hDC, vector[0].x[j], vector[0].y[j]);
	                   }
	             };
	       ReleaseDC(hWnd,hDC);
               goto Fight;


	   };
	    			
        stop = 0;
	for (i1=0;i1<10;i1++)
         {
 	   if (popcop[i1].Fitness ==0)
 	     { 
	       Afiseaza_Drum2(hWnd,obs,rob,i1,vector);
		 
	       rem=i1;
               stop=1;
	       goto Exit;
	    //   goto Fight;
	     };
	 
          };
       }

   while (  stop == 0);
   Exit:


   for (i=0;i<300;i++)
      if ( (vector[rem].x[i] ==0)&(vector[rem].y[i]==0) )
		mer =i; 
sin =0;
do {

   while(  PeekMessage(&msg, hWnd,WM_MOUSEFIRST,WM_MOUSELAST, PM_NOYIELD|PM_REMOVE) )
	    {
	      if (msg.message ==WM_LBUTTONDOWN)
		{
		
			 sin =1;
		  
                 };
	      TranslateMessage(&msg);
              DispatchMessage(&msg);
	    };
   }
while (sin !=1);


  
nr=0;
do  {
      
	gettime(&t1);
	m11=60*t1.ti_min + t1.ti_sec;
	 
	do{
            gettime (&t2);
            m2=60*t2.ti_min +t2.ti_sec;


          }
	while (m2-m11<=2 );
                 
	  
		  
	while(  PeekMessage(&msg, hWnd,WM_MOUSEFIRST,WM_MOUSELAST, PM_NOYIELD|PM_REMOVE) )
	  {
	    if (msg.message ==WM_LBUTTONDOWN)
		{
                  
		  xMouse = LOWORD(msg.lParam);
		  yMouse = HIWORD(msg.lParam);
		  obs[con].xleft_up = xMouse-30;
                  obs[con].yleft_up = yMouse-30;
                  obs[con].xright_down = xMouse +30 ;
                  obs[con].yright_down = yMouse+30;
                  obs[con].xCentru = xMouse;
		  obs[con].yCentru = yMouse;
		  hDC =GetDC(hWnd);
		  Ellipse(hDC,obs[con].xleft_up , obs[con].yleft_up , obs[con].xright_down , obs[con].yright_down ) ;
		  ReleaseDC(hWnd,hDC);
		  con=con+1;   
                       
                 };
	    TranslateMessage(&msg);
            DispatchMessage(&msg);
          };
	 nr =nr+1;
         rob =Sa_stie_si_rob(rob,vector,nr,rem,hWnd);

           
	 if ( test(obs,rob,x1,y1,d,con)==1 )
	     {
	       rob = Sa_stie_si_rob(rob,vector,nr-1,rem,hWnd);
	       hDC =GetDC(hWnd);      
               hpen = CreatePen(PS_SOLID|PS_INSIDEFRAME,1, RGB(255,255 , 255));
	       hpenOld = SelectObject(hDC,hpen);
               Ellipse(hDC,  rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down);
	       SelectObject(hDC, hpenOld);
	       DeleteObject(hpen);
	       ReleaseDC(hWnd,hDC);
	  
	       rob =Sa_stie_si_rob (rob,vector,nr,rem,hWnd);
	       hDC =GetDC(hWnd);
	       s1 = rob.xCentru;
               s2 = rob.yCentru;
	       rob.xleft_up = s1-20;
               rob.yleft_up = s2-20;
	       rob.xright_down = s1+20;
               rob.yright_down = s2+20;   
	  
              
	       Ellipse(hDC,  rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down);

	       for (j=0;j<300;j++)
	           if( j !=0 )
	             {	          
	                if ((vector[rem].x[j] != 0)&(vector[rem].y[j] != 0) )
	                  { 
       	                    MoveTo(hDC, vector[rem].x[j-1], vector[rem].y[j-1]);
		            LineTo(hDC, vector[rem].x[j], vector[rem].y[j]);
	                   }
	             };
	       ReleaseDC(hWnd,hDC);
	                   
	       if( (rob.xCentru ==vector[rem].x[mer-1] )&(rob.yCentru==vector[rem].y[mer-1] ))
		  goto Fight;

                
	      }
         else
	 
	     {


	       rob =  Sa_stie_si_rob(rob,vector,nr-1,rem,hWnd);
	       hDC =GetDC(hWnd);
               hpen = CreatePen(PS_SOLID|PS_INSIDEFRAME,1, RGB(255,255 , 255));
	       hpenOld = SelectObject(hDC,hpen);
               Ellipse(hDC,  rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down);
	       SelectObject(hDC, hpenOld);
	       DeleteObject(hpen);
	       ReleaseDC(hWnd,hDC);


               hDC =GetDC(hWnd);
               rob = Sa_stie_si_rob(rob,vector,nr-2,rem,hWnd);
               
	       s1 = rob.xCentru;
	       s2 = rob.yCentru;
	       xmem = s1;
               ymem = s2;
	       rob.xleft_up = s1-20;
               rob.yleft_up = s2-20;
	       rob.xright_down = s1+20;
               rob.yright_down = s2+20;   

	       Ellipse(hDC,  rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down);
	       for (i=0;i<30;i++)
		   Ellipse(hDC,obs[i].xleft_up , obs[i].yleft_up , obs[i].xright_down , obs[i].yright_down ) ;
	       ReleaseDC(hWnd,hDC);


	       hDC =GetDC(hWnd);

	       hpen = CreatePen(PS_SOLID|PS_INSIDEFRAME,1, RGB(255,255 , 255));
	       hpenOld = SelectObject(hDC,hpen);

		       	for (j=0;j<300;j++)
	                   if( j !=0 )
	                     {	          
	                       if ((vector[rem].x[j] != 0)&(vector[rem].y[j] != 0) )
	                          { 
       	                            MoveTo(hDC, vector[rem].x[j-1], vector[rem].y[j-1]);
		                    LineTo(hDC, vector[rem].x[j], vector[rem].y[j]);
	                          }
			    };
	       SelectObject(hDC, hpenOld);
	       DeleteObject(hpen);

	       
	       ReleaseDC(hWnd,hDC);

	       logic =1;

	       goto Reluare ;   
	      }
     } 
while ((rob.xCentru !=vector[rem].x[mer-1] )&(rob.yCentru!=vector[rem].y[mer-1] )  );

    
Fight:

       
   return 0;
}





FAR PASCAL Afiseaza_Drum2 (hWnd,obs,rob,i,vector)
HWND hWnd;
OBSTACOL obs[30];
ROBOT rob;
int i;
traiectorie vector[10];
{
   
     int ic,j;
     short nLength;
     char szBuffer[100];
     HDC hDC;
     hDC = GetDC(hWnd);
 

     MoveTo(hDC,10,25);
     LineTo(hDC,10,480);
     LineTo(hDC,750,480);
     LineTo(hDC,750,25);   
     LineTo(hDC,10,25);
     nLength = sprintf(szBuffer,"Terrain Map 2 ");
     TextOut (hDC,352,5,szBuffer,nLength);




     
      


        obs[0].xleft_up = 30;
        obs[0].yleft_up = 400 ;
        obs[0].xright_down =90; 
	obs[0].yright_down =460;
        obs[0].xCentru = 60;
        obs[0].yCentru = 430;
        
 
        obs[1].xleft_up =210;	
        obs[1].yleft_up = 300; 
        obs[1].xright_down =270; 
        obs[1].yright_down =360; 
        obs[1].xCentru = 240;
        obs[1].yCentru = 330;
        
         
        obs[2].xleft_up =310;	
        obs[2].yleft_up =200; 
        obs[2].xright_down =370; 
        obs[2].yright_down =260; 
        obs[2].xCentru = 340;
        obs[2].yCentru = 230;
        
      
        obs[3].xleft_up =410;	
        obs[3].yleft_up =100; 
        obs[3].xright_down =470; 
        obs[3].yright_down =160; 
        obs[3].xCentru = 440;
        obs[3].yCentru = 130;
        


	obs[4].xleft_up = 110;
        obs[4].yleft_up =390; 
        obs[4].xright_down =170; 
        obs[4].yright_down =450; 
        obs[4].xCentru =140;
	obs[4].yCentru =420;


	obs[5].xleft_up = 30;
        obs[5].yleft_up = 400 ;
        obs[5].xright_down =90; 
	obs[5].yright_down =460;
        obs[5].xCentru = 60;
        obs[5].yCentru = 430;
        
 
        obs[6].xleft_up =210;	
        obs[6].yleft_up = 300; 
        obs[6].xright_down =270; 
        obs[6].yright_down =360; 
        obs[6].xCentru = 240;
        obs[6].yCentru = 330;
        
         
        obs[7].xleft_up =310;	
        obs[7].yleft_up =200; 
        obs[7].xright_down =370; 
        obs[7].yright_down =260; 
        obs[7].xCentru = 340;
        obs[7].yCentru = 230;
        
      
        obs[8].xleft_up =410;	
        obs[8].yleft_up =100; 
        obs[8].xright_down =470; 
        obs[8].yright_down =160; 
        obs[8].xCentru = 440;
        obs[8].yCentru = 130;
        


	obs[9].xleft_up = 110;
        obs[9].yleft_up =390; 
        obs[9].xright_down =170; 
        obs[9].yright_down =450; 
        obs[9].xCentru =140;
	obs[9].yCentru =420;

	
	obs[10].xleft_up = 110;
        obs[10].yleft_up =390; 
        obs[10].xright_down =170; 
        obs[10].yright_down =450; 
        obs[10].xCentru =140;
	obs[10].yCentru =420;

       for (ic=0;ic<30;ic++)
	  Ellipse(hDC,obs[ic].xleft_up , obs[ic].yleft_up , obs[ic].xright_down , obs[ic].yright_down ) ;

	for (j=0;j<300;j++)
	 if( j !=0 )
	   {
	   
	    if ((vector[i].x[j] != 0)&(vector[i].y[j] != 0) )
	      { 
       	        MoveTo(hDC, vector[i].x[j-1], vector[i].y[j-1]);
		LineTo(hDC, vector[i].x[j], vector[i].y[j]);
	      }
	   };

	ReleaseDC (hWnd,hDC );



	return 1;
}  





OBSTACOL* FAR PASCAL Harta2(hWnd ,obs,rob)
HWND hWnd;
OBSTACOL obs[30];
ROBOT rob;

{
       HDC hDC;
     int i;
     short nLength;
     char szBuffer[100];
  

     
      

	obs[0].xleft_up = 30;
        obs[0].yleft_up = 400 ;
        obs[0].xright_down =90; 
	obs[0].yright_down =460;
        obs[0].xCentru = 60;
        obs[0].yCentru = 430;
        
 
        obs[1].xleft_up =210;	
        obs[1].yleft_up = 300; 
        obs[1].xright_down =270; 
        obs[1].yright_down =360; 
        obs[1].xCentru = 240;
        obs[1].yCentru = 330;
        
         
        obs[2].xleft_up =310;	
        obs[2].yleft_up =200; 
        obs[2].xright_down =370; 
        obs[2].yright_down =260; 
        obs[2].xCentru = 340;
        obs[2].yCentru = 230;
        
      
        obs[3].xleft_up =410;	
        obs[3].yleft_up =100; 
        obs[3].xright_down =470; 
        obs[3].yright_down =160; 
        obs[3].xCentru = 440;
        obs[3].yCentru = 130;
        


	obs[4].xleft_up = 110;
        obs[4].yleft_up =390; 
        obs[4].xright_down =170; 
        obs[4].yright_down =450; 
        obs[4].xCentru =140;
	obs[4].yCentru =420;


	obs[5].xleft_up = 30;
        obs[5].yleft_up = 400 ;
        obs[5].xright_down =90; 
	obs[5].yright_down =460;
        obs[5].xCentru = 60;
        obs[5].yCentru = 430;
        
 
        obs[6].xleft_up =210;	
        obs[6].yleft_up = 300; 
        obs[6].xright_down =270; 
        obs[6].yright_down =360; 
        obs[6].xCentru = 240;
        obs[6].yCentru = 330;
        
         
        obs[7].xleft_up =310;	
        obs[7].yleft_up =200; 
        obs[7].xright_down =370; 
        obs[7].yright_down =260; 
        obs[7].xCentru = 340;
        obs[7].yCentru = 230;
        
      
        obs[8].xleft_up =410;	
        obs[8].yleft_up =100; 
        obs[8].xright_down =470; 
        obs[8].yright_down =160; 
        obs[8].xCentru = 440;
        obs[8].yCentru = 130;
        


	obs[9].xleft_up = 110;
        obs[9].yleft_up =390; 
        obs[9].xright_down =170; 
        obs[9].yright_down =450; 
        obs[9].xCentru =140;
	obs[9].yCentru =420;

	
	obs[10].xleft_up = 110;
        obs[10].yleft_up =390; 
        obs[10].xright_down =170; 
        obs[10].yright_down =450; 
        obs[10].xCentru =140;
	obs[10].yCentru =420;






	   
     hDC = GetDC(hWnd);
 
     MoveTo(hDC,10,25);
     LineTo(hDC,10,480);
     LineTo(hDC,750,480);
     LineTo(hDC,750,25);   
     LineTo(hDC,10,25);
     nLength = sprintf(szBuffer,"Terrain Map 2 ");
     TextOut (hDC,352,5,szBuffer,nLength);

     for (i=0;i<30;i++) 
	  Ellipse(hDC,obs[i].xleft_up , obs[i].yleft_up , obs[i].xright_down , obs[i].yright_down ) ;



        ReleaseDC (hWnd,hDC ); 

	return obs;
}  

   



int  FAR PASCAL Go3 (rob,hWnd,vector,popcop,poppar,lParam,wParam)
ROBOT rob;
HWND hWnd;
traiectorie vector[10];
CROMOZOM popcop[10];
CROMOZOM poppar[10];
LPARAM lParam;
WPARAM wParam;
{
   short nLength;
   int z;
   char szBuffer[100];
   HDC hDC;
   Comanda m;
   int i,j,i1;
   int stop,moc;
   int s,s1,s2,sin;
   int top[3];
   int l1,m1,n1,k;
   unsigned long f1,f;
   MSG msg;
   int f2;
   struct time t1,t2;
   unsigned long  m11,m2;
   int xMouse,yMouse;
   PAINTSTRUCT ps;
   POINT pon;
   HPEN  hpen,hpenOld ; 
   int ionut,camelia;
   int tut=0;



do {
     if (tut <1)
       {
  	   while(  PeekMessage(&msg, hWnd,WM_MOUSEFIRST,WM_MOUSELAST, PM_NOYIELD|PM_REMOVE) )
	    {
	      if (msg.message ==WM_LBUTTONDOWN)
		{
                  
		  xMouse = LOWORD(msg.lParam);
		  yMouse = HIWORD(msg.lParam);
		  ri = xMouse;
                  ti = yMouse;
		  rob.xleft_up = xMouse-20;
                  rob.yleft_up = yMouse-20;
                  rob.xright_down = xMouse +20;
                  rob.yright_down = yMouse +20;
                  rob.xCentru = xMouse;
		  rob.yCentru = yMouse;
		  hDC =GetDC(hWnd);
		  Ellipse(hDC,rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down ) ;
		  ReleaseDC(hWnd,hDC);   
                  tut=1;     
                 };
	      TranslateMessage(&msg);
	      DispatchMessage(&msg);
            };
	}
      else
        {
	    while(  PeekMessage(&msg, hWnd,WM_MOUSEFIRST,WM_MOUSELAST, PM_NOYIELD|PM_REMOVE) )
	     {
	        if (msg.message ==WM_LBUTTONDOWN)
		  {
                  
		     x_final = LOWORD(msg.lParam);
		     y_final = HIWORD(msg.lParam);
		   
		     hDC =GetDC(hWnd);
		     SetPixel(hDC,x_final,y_final,RGB(0,0,0) );
		     ReleaseDC(hWnd,hDC);
               
	      
                     tut=2;     
                  };
	        TranslateMessage(&msg);
                DispatchMessage(&msg);
            };
         }



}
while (tut < 2);


   Reluare :    
   n=0;
   for (i=0;i<10;i++)
      {
       poppar[i].Fitness = 0;
       popcop[i].Fitness = 0 ;
      };
   L_init_var_ling(pvo,pvm,pvn,hWnd);
   Load_genetic_init(poppar);
   LoadInitial(c);  
   for(i=0;i<10;i++)
     poppar[i].Fitness =0;
   pas =0;
     for(i=0;i<10 ;i++)
       {
         for(j=0;j<300;j++)
           { 
   	  if(j==0)
	    {
	     if(logic != 1)
              {
	      vector[i].x[0] =ri; 
	      vector[i].y[0] =ti;
	      }
	     else
	      {
	      vector[i].x[0] = xmem;
	      vector[j].y[0] = ymem; 
	       }
	    }
 	   else
  	    {
	      vector[i].x[j] = 0;
	      vector[i].y[j] = 0;
             }
           };
        };
    Sa_stie_si_rob(rob,vector,pas,0,hWnd);
    pas =1;
    ionut = 0;


    do
     {
	  
	   Intermediar1(tip,obs,x1,y1,rob,TipVar1,TipVar2,vertical,hWnd,d);

	  

           com = c[tip[2]].b[tip[1]].a[tip[0]];
    	   m= Com (com,hWnd); 
 
           Deplasare (rob,m,0,pas,x1,y1,vector,poz);
	 
	   rob=  Sa_stie_si_rob(rob,vector,pas,0,hWnd);

	   f1= CalculezFitnes1 (0,poppar,obs,rob,x1,y1);
	   pas=pas+1;   


//1
	if (     (ri >= x_final)&(ti <= y_final)&( rob.xCentru <= (x_final+10) )&( rob.yCentru >= (y_final-6) ) )
	           ionut =1;     
//2
	if (     (ri >= x_final)&(ti >= y_final)&( rob.xCentru <= (x_final+15) )&( rob.yCentru <= (y_final+15) ) )
		   ionut =1;
//0		        
	if (     (ri <= x_final)&(ti <= y_final)&( rob.xCentru >= (x_final-10) )&( rob.yCentru >= (y_final-6) ) )
		   ionut =1;
//3		        
	if (     (ri <= x_final)&(ti >= y_final)&( rob.xCentru >= (x_final-15) )&( rob.yCentru <= (y_final+15) ) )
	           ionut =1;     


      }
   while (ionut != 1);
   for (i=0;i<10;i++)
          poppar[i].Fitness = f1 ;
    if (poppar[0].Fitness ==0)
      {
	
		Afiseaza_Drum3(hWnd,obs,rob,0,vector);
           //     goto Fight;
   	   	goto Exit;
      };
     
     
	          
    n=0;
    initial =0;
    
   do {
             n=n+1;
	     for(i=0;i<10;i++)
	         for(j=0;j<1000;j++)
	            {             
                      vector[i].x[j] =0 ;
		      vector[i].y[j] = 0 ;
		    };      

       genetic(initial,hWnd,n);  

       initial=1;   
       for (i=0 ;i<10;i++)
        {
              for(j=0;j<1000;j++)
	            {             
		      vector[i].x[j] =0 ;
		      vector[i].y[j] =0 ;
		    };
       

        pas=0;
        Load (popcop,c,i,hWnd);                         
 
        L_init_var_ling(pvo,pvm,pvn,hWnd);
	Modific_var_ling (popcop,i,pvo,pvm,pvn,hWnd) ; 
	
	if (logic != 1)
           {
	      vector[i].x[0] = ri;
	      vector[i].y[0] = ti; 
           }
        else
	   {
	      vector[i].x[0] = xmem ;
	      vector[i].y[0] = ymem ;
	   } 
        rob =Sa_stie_si_rob(rob,vector,0,i,hWnd);
        moc=0;
	for(moc=0;moc<300;moc++)
	     {
           	       pas=pas+1;
		       Intermediar1(tip,obs,x1,y1,rob,TipVar1,TipVar2,vertical,hWnd,d);
		       com = c[tip[2]].b[tip[1]].a[tip[0]];
	               m= Com (com,hWnd);
		       Deplasare (rob,m,i,pas,x1,y1,vector,poz);
		       rob=  Sa_stie_si_rob(rob,vector,pas,i,hWnd);
		       f= CalculezFitnes (i,popcop,obs,rob,x1,y1);




		       if(     (rob.xCentru >= (x_final-15)) & (rob.yCentru >= (y_final-15)) & (rob.xCentru <= (x_final+15)) & ( rob.yCentru <=(y_final+15))  )//|| ( (rob.xCentru >= (x_final-15)) & (rob.yCentru <= (y_final+15)) ) || (  (rob.xCentru <= (x_final+15)) & (rob.yCentru >= (y_final-15))  )  ||  (  (rob.xCentru <= (x_final+15)) & (rob.yCentru <= (y_final+15)) ) )
	   	          {  
			      
                             goto Label;
                          };           
              };
   
		if  ( (rob.xCentru <(x_final-50) ) ||(rob.yCentru<(y_final-35))||(rob.xCentru >(x_final+50))||(rob.yCentru >(y_final+35)) )
                      {
			     popcop[i].Fitness = f +5000 ;
		       }
		else
		      {
                       Label:
                       popcop[i].Fitness =f;
		       }
			  
                           
    	                       /*   hDC =GetDC(hWnd);
                           
                                  nLength =sprintf(szBuffer," %lu       ",poppar[i].Fitness);
	                          TextOut(hDC,15*i,15*i,szBuffer,nLength);      
				  ReleaseDC(hWnd,hDC);   
                                */


        };
       	

     /* HERE  YOU  CAN MODIFY THE VALUE OF N */

       if (n >10000 )
	  {
	      hDC =GetDC(hWnd);
	      for (j=0;j<300;j++)
	           if( j !=0 )
	             {	          
	                if ((vector[rem].x[j] != 0)&(vector[rem].y[j] != 0) )
	                  { 
       	                    MoveTo(hDC, vector[0].x[j-1], vector[0].y[j-1]);
		            LineTo(hDC, vector[0].x[j], vector[0].y[j]);
	                   }
	             };
	       ReleaseDC(hWnd,hDC);
               goto Fight;


	   };
        stop = 0;
	for (i1=0;i1<10;i1++)
         {
 	   if (popcop[i1].Fitness ==0)
 	     { 
	       Afiseaza_Drum3(hWnd,obs,rob,i1,vector);
		 
	       rem=i1;
               stop=1;
	       goto Exit;
	    //   goto Fight;
	     };
	 
          };
       }

   while (  stop == 0);
   Exit:


   for (i=0;i<300;i++)
      if ( (vector[rem].x[i] ==0)&(vector[rem].y[i]==0) )
		mer =i; 
sin =0;
do {

   while(  PeekMessage(&msg, hWnd,WM_MOUSEFIRST,WM_MOUSELAST, PM_NOYIELD|PM_REMOVE) )
	    {
	      if (msg.message ==WM_LBUTTONDOWN);
		{
		
			 sin =1;
		  
                 };
	      TranslateMessage(&msg);
              DispatchMessage(&msg);
	    };
   }
while (sin !=1);


  
nr=0;
do  {
      
	gettime(&t1);
	m11=60*t1.ti_min + t1.ti_sec;
	 
	do{
            gettime (&t2);
            m2=60*t2.ti_min +t2.ti_sec;


          }
	while (m2-m11<=2 );
                 
	  
		  
	while(  PeekMessage(&msg, hWnd,WM_MOUSEFIRST,WM_MOUSELAST, PM_NOYIELD|PM_REMOVE) )
	  {
	    if (msg.message ==WM_LBUTTONDOWN)
		{
                  
		  xMouse = LOWORD(msg.lParam);
		  yMouse = HIWORD(msg.lParam);
		  obs[con].xleft_up = xMouse-30;
                  obs[con].yleft_up = yMouse-30;
                  obs[con].xright_down = xMouse +30 ;
                  obs[con].yright_down = yMouse+30;
                  obs[con].xCentru = xMouse;
		  obs[con].yCentru = yMouse;
		  hDC =GetDC(hWnd);
		  Ellipse(hDC,obs[con].xleft_up , obs[con].yleft_up , obs[con].xright_down , obs[con].yright_down ) ;
		  ReleaseDC(hWnd,hDC);
		  con=con+1;   
                       
                 };
	    TranslateMessage(&msg);
            DispatchMessage(&msg);
          };
	 nr =nr+1;
         rob =Sa_stie_si_rob(rob,vector,nr,rem,hWnd);

           
	 if ( test(obs,rob,x1,y1,d,con)==1 )
	     {
	       rob = Sa_stie_si_rob(rob,vector,nr-1,rem,hWnd);
	       hDC =GetDC(hWnd);      
               hpen = CreatePen(PS_SOLID|PS_INSIDEFRAME,1, RGB(255,255 , 255));
	       hpenOld = SelectObject(hDC,hpen);
               Ellipse(hDC,  rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down);
	       SelectObject(hDC, hpenOld);
	       DeleteObject(hpen);
	       ReleaseDC(hWnd,hDC);
	  
	       rob =Sa_stie_si_rob (rob,vector,nr,rem,hWnd);
	       hDC =GetDC(hWnd);
	       s1 = rob.xCentru;
               s2 = rob.yCentru;
	       rob.xleft_up = s1-20;
               rob.yleft_up = s2-20;
	       rob.xright_down = s1+20;
               rob.yright_down = s2+20;   
	  
              
	       Ellipse(hDC,  rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down);

	       for (j=0;j<300;j++)
	           if( j !=0 )
	             {	          
	                if ((vector[rem].x[j] != 0)&(vector[rem].y[j] != 0) )
	                  { 
       	                    MoveTo(hDC, vector[rem].x[j-1], vector[rem].y[j-1]);
		            LineTo(hDC, vector[rem].x[j], vector[rem].y[j]);
	                   }
	             };
	       ReleaseDC(hWnd,hDC);
	                   

	      
	      }
         else
	 
	     {
	       if( (rob.xCentru ==vector[rem].x[mer-1] )&(rob.yCentru==vector[rem].y[mer-1] ))
		  goto Fight;

	       rob =  Sa_stie_si_rob(rob,vector,nr-1,rem,hWnd);
	       hDC =GetDC(hWnd);
               hpen = CreatePen(PS_SOLID|PS_INSIDEFRAME,1, RGB(255,255 , 255));
	       hpenOld = SelectObject(hDC,hpen);
               Ellipse(hDC,  rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down);
	       SelectObject(hDC, hpenOld);
	       DeleteObject(hpen);
	       ReleaseDC(hWnd,hDC);


               hDC =GetDC(hWnd);
               rob = Sa_stie_si_rob(rob,vector,nr-2,rem,hWnd);
               
	       s1 = rob.xCentru;
	       s2 = rob.yCentru;
	       xmem = s1;
               ymem = s2;
	       rob.xleft_up = s1-20;
               rob.yleft_up = s2-20;
	       rob.xright_down = s1+20;
               rob.yright_down = s2+20;   

	       Ellipse(hDC,  rob.xleft_up , rob.yleft_up , rob.xright_down , rob.yright_down);
	       for (i=0;i<30;i++)
		   Ellipse(hDC,obs[i].xleft_up , obs[i].yleft_up , obs[i].xright_down , obs[i].yright_down ) ;
	       ReleaseDC(hWnd,hDC);


	       hDC =GetDC(hWnd);

	       hpen = CreatePen(PS_SOLID|PS_INSIDEFRAME,1, RGB(255,255 , 255));
	       hpenOld = SelectObject(hDC,hpen);

		       	for (j=0;j<300;j++)
	                   if( j !=0 )
	                     {	          
	                       if ((vector[rem].x[j] != 0)&(vector[rem].y[j] != 0) )
	                          { 
       	                            MoveTo(hDC, vector[rem].x[j-1], vector[rem].y[j-1]);
		                    LineTo(hDC, vector[rem].x[j], vector[rem].y[j]);
	                          }
			    };
	       SelectObject(hDC, hpenOld);
	       DeleteObject(hpen);

	       
	       ReleaseDC(hWnd,hDC);

	       logic =1;

	       goto Reluare ;   
	      }
     } 
while ((rob.xCentru !=vector[rem].x[mer-1] )&(rob.yCentru!=vector[rem].y[mer-1] )  );


Fight:

       
   return 0;
}





FAR PASCAL Afiseaza_Drum3 (hWnd,obs,rob,i,vector)
HWND hWnd;
OBSTACOL obs[30];
ROBOT rob;
int i;
traiectorie vector[10];
{
   
     int ic,j;
     short nLength;
     char szBuffer[100];
     HDC hDC;
     hDC = GetDC(hWnd);
 

     MoveTo(hDC,10,25);
     LineTo(hDC,10,480);
     LineTo(hDC,750,480);
     LineTo(hDC,750,25);   
     LineTo(hDC,10,25);
     nLength = sprintf(szBuffer,"Terrain Map 1 ");
     TextOut (hDC,352,5,szBuffer,nLength);


    

       for (ic=0;ic<30;ic++)
	  Ellipse(hDC,obs[ic].xleft_up , obs[ic].yleft_up , obs[ic].xright_down , obs[ic].yright_down ) ;

	for (j=0;j<300;j++)
	 if( j !=0 )
	   {
	   
	    if ((vector[i].x[j] != 0)&(vector[i].y[j] != 0) )
	      { 
       	        MoveTo(hDC, vector[i].x[j-1], vector[i].y[j-1]);
		LineTo(hDC, vector[i].x[j], vector[i].y[j]);
	      }
	   };

	ReleaseDC (hWnd,hDC );



	return 0;
}  





OBSTACOL* FAR PASCAL Harta3(hWnd ,obs,rob)
HWND hWnd;
OBSTACOL obs[30];
ROBOT rob;

{
       HDC hDC;
     int i;
     short nLength;
     char szBuffer[100];
  

     
	   
     hDC = GetDC(hWnd);
     MoveTo(hDC,10,25);
     LineTo(hDC,10,480);
     LineTo(hDC,750,480);
     LineTo(hDC,750,25);   
     LineTo(hDC,10,25);
     nLength = sprintf(szBuffer,"Terrain Map 1 ");
     TextOut (hDC,352,5,szBuffer,nLength);

     for (i=0;i<30;i++) 
	  Ellipse(hDC,obs[i].xleft_up , obs[i].yleft_up , obs[i].xright_down , obs[i].yright_down ) ;



        ReleaseDC (hWnd,hDC ); 

	return obs;
}  

