//HALİL ŞEN 230306028

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 



typedef struct Hucre { 
    int deger;      
    int satir;      
    int sutun;      
    struct Hucre* sonraki;  
}hucre;

typedef struct SudokuTahtasi{ 
    struct Hucre* tahta[9];    
}sudokutahta; 
 

void TahtaBaslat(sudokutahta* tahta)
{
  
   int deger;

   for (int i = 0; i < 9; i++)
   {
        tahta->tahta[i] = (hucre*)malloc(sizeof(hucre)*9);
        for (int j = 0; j < 9; j++)
        {   
            deger = 0;
            tahta->tahta[i][j].deger = deger;
            tahta->tahta[i][j].satir = i;
            tahta->tahta[i][j].sutun = j;

        }
   }
}

void SudokuGiris(sudokutahta* tahta)
{
    int deger;

   
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {   

            printf("Su konum icin deger giriniz %d,%d:\n",i+1,j+1);
            scanf("%d",&deger);
            tahta->tahta[i][j].deger = deger;
           
        }
    }


}
void SudokuYazdir(sudokutahta* tahta)
{
    for (int k = 0; k < 9; k++)
    {
        for (int l = 0; l < 9; l++)
        {
            printf("%d ",tahta->tahta[k][l].deger);
        }
        printf("\n");
    }
}


bool SatirdaVarMi(sudokutahta* tahta, int satir, int num)
{
     
    for (int i = 0; i < 9; i++)
    {
        if (tahta->tahta[satir][i].deger == num)
        {
            return true;
        }
        
    }
    return false;

}

bool SutundaVarMi(sudokutahta* tahta, int sutun, int num)
{
    
    for (int i = 0; i < 9; i++)
    {   
        if ( tahta->tahta[i][sutun].deger == num)
        {
            return true;
        }
        
    }
    return false;
}
 
bool KutucuktaVarmi(sudokutahta* tahta, int baslangicSatiri, int baslangicSutunu, int num)
{
    
    if (baslangicSutunu <3)
    {
        baslangicSutunu = 0;
    }
    else if(baslangicSutunu <6 && baslangicSutunu >=3)
    {
        baslangicSutunu = 3;
    }    
    else if (baslangicSutunu <9 && baslangicSutunu >= 6)
    {
        baslangicSutunu = 6;
    }
    if (baslangicSatiri < 3)
    {
        baslangicSatiri =   0;

    }
    else if(baslangicSatiri <6 && baslangicSatiri >= 3)
    {
        baslangicSatiri =   3;
    }
    else if(baslangicSatiri < 9 && baslangicSatiri >=6)
    {
        baslangicSatiri =  6;
    }

    for (int i = baslangicSatiri; i < baslangicSatiri + 3 ; i++)
    {
        for (int j = baslangicSutunu; j <baslangicSutunu+ 3; j++)
        {
            if (tahta->tahta[i][j].deger == num)
            {
                return true;
            }
        }
    }
    
    return false;


}

bool GecerliYerlestirmemi(sudokutahta* tahta, int satir, int sutun, int num)
{
   if (SatirdaVarMi(tahta,satir,num) || SutundaVarMi(tahta,sutun,num) || KutucuktaVarmi(tahta,satir,sutun,num))
   {
        return false;
   }
   else
   {
        return true;
   }
   
    
} 

 

hucre* bosHucreBul(sudokutahta* tahta)
{
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {   
            if (tahta->tahta[i][j].deger == 0)
            {
                return &tahta->tahta[i][j];
            }
        }   
    }
    
    return NULL;
 
}


int SudokuCoz(sudokutahta* tahta)
{
    if(bosHucreBul(tahta) == NULL)
    {
        return true;
    }
    else
    {
        hucre *bos_hucre = bosHucreBul(tahta);
        int satir = bos_hucre->satir;
        int sutun = bos_hucre->sutun;
    


        for (int j = 0; j < 9; j++)
        {
            if (GecerliYerlestirmemi(tahta,satir,sutun,j+1))
            {
                tahta->tahta[satir][sutun].deger = j+1;

                if(SudokuCoz(tahta))
                {
                    return true;
                }

                tahta->tahta[satir][sutun].deger = 0;
            }
            
        }
        return false;        
    }
}


void bellegiTemizle(sudokutahta* tahta) {
    for (int i = 0; i < 9; i++) {
        if (tahta->tahta[i] != NULL) {
            free(tahta->tahta[i]);
            tahta->tahta[i] = NULL;  
        }
    }
}
 


int main() { 
    sudokutahta sudkoutahta; 

    TahtaBaslat(&sudkoutahta); 
    SudokuGiris(&sudkoutahta); 
    printf("Girilen Sudoku Tahtasi:\n");
    SudokuYazdir(&sudkoutahta); 
     

 

    
    if (SudokuCoz(&sudkoutahta))
    { 
        printf("Cozulmus Sudoku Tahtasi:\n" );
        SudokuYazdir(&sudkoutahta); 
    } 
    else 
    { 
        printf("Verilen Sudoku tahtasi icin gecerli bir cozum yok.");
    } 
    bellegiTemizle(&sudkoutahta); 
    
    return 0; 
}