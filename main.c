#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>



const char matrix_bigram_strings[10][3] ={"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};


const char matrix_trigram_strings[10][4]={"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};



const char languages[2][8]={"english", "german"};



//Ýngilizce dilinin frekans deðerleri

const float frequency_eng[20]={ 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };


//Almanca dilinin frekans deðerleri

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




	printf("bir metin  giriniz : "); // metni alýyoruz

   char str[50];
   gets(str);

	printf("%s\n",str);

	// kültür fonksiyonunu çaðýrdým. calculate ve delect fonksiyonunu çaðýrdým
	filter_str(str);

	calculate_distances();
	detect_lang();

	return 0;

}


// uzunluk tanýmlayýp stringin uzunluðunu uzunluða tanýmladým.

void filter_str(char str[])
	{

	int uzunluk = strlen(str);

	int i;
// stringin  uzunluðu dönüp yabancý karekterleri ayýrt edip yabancý karekterlerin yerine boþluk karekterini koyuyoruz.
	for(i=0;i<uzunluk;i++)
	{
		if(!isalpha(str[i]))
		{
			str[i]=' ';
		}
	}

	printf("Filtrelenmis metin:\n");
	printf("%s\n", str);

	// aþaðýdaki fonksiyonlarla bigram ve trigram fonksiyonlarýný çaðýrdým
	calculate_frequencies_bi(str);
	calculate_frequencies_tri(str);

}





void calculate_frequencies_bi(char str[])
{
	int i,j;

	// bulduðumuz bigram frekans matrisini oluþturuyoruz.
	int frek[10];

  // bütün elemanlarý sýfýrladýk.
	for(i=0;i<10;i++)
	{
		frek[i]=0;
	}

	for(i=0;i<strlen(str);i++)

	{
		str[i] = tolower(str[i]); //bütün elemanlarý küçük harfe dönüþtürdük.
	}


	for(i = 0;i<10;i++)
		for(j=0;j<strlen(str)-1;j++)
            // bigramlarý metin içinde aradým.
		{
			if(matrix_bigram_strings[i][0]==str[j]&&matrix_bigram_strings[i][1]==str[j+1])
				frek[i]++;
		}

	printf("\nbigram frekans:\n");
	for(i =0;i<10;i++)

        // bulduðumuz frekanslarý ekrana yazdýrýp global calculated_frequencies atamasýný saðladýk.
	{
		printf("%s : %d\n",matrix_bigram_strings[i],frek[i]);
		calculated_frequencies[i]=frek[i];
	}
}


//
void calculate_frequencies_tri(char str[])
{
	int i,j;
	// bulduðumuz trigram frekans matrisini oluþturuyoruz.

	int frek[10];

// bütün elemanlarý sýfýrladýk.

	for(i=0;i<10;i++)
	{
		frek[i]=0;
	}

	for(i=0;i<strlen(str);i++)

	{
		str[i] = tolower(str[i]);  //bütün elemanlarý küçük harfe dönüþtürdük.
	}

	for(i = 0;i<10;i++)
		for(j=0;j<strlen(str)-2;j++)

            // trigramlarý metin içinde aradým.
		{
			if(matrix_trigram_strings[i][0]==str[j]&&matrix_trigram_strings[i][1]==str[j+1]&&matrix_trigram_strings[i][2]==str[j+2])
				frek[i]++;
		}
	printf("\ntrigram frekans:\n");
	for(i =0;i<10;i++)

        // bulduðumuz frekanslarý ekrana yazdýrýp global calculated_frequencies atamasýný saðladýk.

	{
		printf("%s : %d\n",matrix_trigram_strings[i],frek[i]);
		calculated_frequencies[i+10]=frek[i];
	}
}


void calculate_distances()
{
	int i;
	float toplam = 0;

	// öklid uzaklýðý ile mesafeyi hesapladýk.
	for(i = 0;i<20;i++)
	{
		toplam += kare(calculated_frequencies[i]-frequency_eng[i]);
	}

 // bulduðumuz deðeri distances matrisinin ilgili indisine atadýk

	distances[0]=sqrt(toplam);

	toplam = 0;
	// öklid uzaklýðý ile mesafeyi hesapladýk.

	for(i = 0;i<20;i++)
	{
		toplam += kare(calculated_frequencies[i]-frequency_germ[i]);
	}
	distances[1]=sqrt(toplam);

	printf("/n uzakliklar");
	printf("\n\n%.2f   :   %.2f\n\n",distances[0],distances[1]);
}
 // uzaklýðý bularak hangi dile yakýn olduðunu kontol ettik.
void detect_lang()
{
	if(distances[0]<distances[1])
		printf("Bu metin Ingilizcedir.\n");
	else
		printf("Bu metin Almancadir.\n");
}


// kareye hesaplamak için fonksiyon oluþturduk
float kare(float sayi)
{
	return sayi*sayi;
} // sayýyý kendisiyle çarpýp geri döndürdük.
