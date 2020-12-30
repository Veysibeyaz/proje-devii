#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>



const char matrix_bigram_strings[10][3] ={"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};


const char matrix_trigram_strings[10][4]={"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};



const char languages[2][8]={"english", "german"};



//�ngilizce dilinin frekans de�erleri

const float frequency_eng[20]={ 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };


//Almanca dilinin frekans de�erleri

const float frequency_germ[20]={ 0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };




float calculated_frequencies[20];

float distances [2]={0,0};




void filter_str(char str[]);

void calculate_frequencies_bi(char str[]);

void calculate_frequencies_tri(char str[]);

void calculate_distances();

void detect_lang();

float kare(float sayi);


int main()

{




	printf("bir metin  giriniz : "); // metni al�yoruz

   char str[50];
   gets(str);

	printf("%s\n",str);

	// k�lt�r fonksiyonunu �a��rd�m. calculate ve delect fonksiyonunu �a��rd�m
	filter_str(str);

	calculate_distances();
	detect_lang();

	return 0;

}


// uzunluk tan�mlay�p stringin uzunlu�unu uzunlu�a tan�mlad�m.

void filter_str(char str[])
	{

	int uzunluk = strlen(str);

	int i;
// stringin  uzunlu�u d�n�p yabanc� karekterleri ay�rt edip yabanc� karekterlerin yerine bo�luk karekterini koyuyoruz.
	for(i=0;i<uzunluk;i++)
	{
		if(!isalpha(str[i]))
		{
			str[i]=' ';
		}
	}

	printf("Filtrelenmis metin:\n");
	printf("%s\n", str);

	// a�a��daki fonksiyonlarla bigram ve trigram fonksiyonlar�n� �a��rd�m
	calculate_frequencies_bi(str);
	calculate_frequencies_tri(str);

}





void calculate_frequencies_bi(char str[])
{
	int i,j;

	// buldu�umuz bigram frekans matrisini olu�turuyoruz.
	int frek[10];

  // b�t�n elemanlar� s�f�rlad�k.
	for(i=0;i<10;i++)
	{
		frek[i]=0;
	}

	for(i=0;i<strlen(str);i++)

	{
		str[i] = tolower(str[i]); //b�t�n elemanlar� k���k harfe d�n��t�rd�k.
	}


	for(i = 0;i<10;i++)
		for(j=0;j<strlen(str)-1;j++)
            // bigramlar� metin i�inde arad�m.
		{
			if(matrix_bigram_strings[i][0]==str[j]&&matrix_bigram_strings[i][1]==str[j+1])
				frek[i]++;
		}

	printf("\nbigram frekans:\n");
	for(i =0;i<10;i++)

        // buldu�umuz frekanslar� ekrana yazd�r�p global calculated_frequencies atamas�n� sa�lad�k.
	{
		printf("%s : %d\n",matrix_bigram_strings[i],frek[i]);
		calculated_frequencies[i]=frek[i];
	}
}


//
void calculate_frequencies_tri(char str[])
{
	int i,j;
	// buldu�umuz trigram frekans matrisini olu�turuyoruz.

	int frek[10];

// b�t�n elemanlar� s�f�rlad�k.

	for(i=0;i<10;i++)
	{
		frek[i]=0;
	}

	for(i=0;i<strlen(str);i++)

	{
		str[i] = tolower(str[i]);  //b�t�n elemanlar� k���k harfe d�n��t�rd�k.
	}

	for(i = 0;i<10;i++)
		for(j=0;j<strlen(str)-2;j++)

            // trigramlar� metin i�inde arad�m.
		{
			if(matrix_trigram_strings[i][0]==str[j]&&matrix_trigram_strings[i][1]==str[j+1]&&matrix_trigram_strings[i][2]==str[j+2])
				frek[i]++;
		}
	printf("\ntrigram frekans:\n");
	for(i =0;i<10;i++)

        // buldu�umuz frekanslar� ekrana yazd�r�p global calculated_frequencies atamas�n� sa�lad�k.

	{
		printf("%s : %d\n",matrix_trigram_strings[i],frek[i]);
		calculated_frequencies[i+10]=frek[i];
	}
}


void calculate_distances()
{
	int i;
	float toplam = 0;

	// �klid uzakl��� ile mesafeyi hesaplad�k.
	for(i = 0;i<20;i++)
	{
		toplam += kare(calculated_frequencies[i]-frequency_eng[i]);
	}

 // buldu�umuz de�eri distances matrisinin ilgili indisine atad�k

	distances[0]=sqrt(toplam);

	toplam = 0;
	// �klid uzakl��� ile mesafeyi hesaplad�k.

	for(i = 0;i<20;i++)
	{
		toplam += kare(calculated_frequencies[i]-frequency_germ[i]);
	}
	distances[1]=sqrt(toplam);

	printf("/n uzakliklar");
	printf("\n\n%.2f   :   %.2f\n\n",distances[0],distances[1]);
}
 // uzakl��� bularak hangi dile yak�n oldu�unu kontol ettik.
void detect_lang()
{
	if(distances[0]<distances[1])
		printf("Bu metin Ingilizcedir.\n");
	else
		printf("Bu metin Almancadir.\n");
}


// kareye hesaplamak i�in fonksiyon olu�turduk
float kare(float sayi)
{
	return sayi*sayi;
} // say�y� kendisiyle �arp�p geri d�nd�rd�k.
