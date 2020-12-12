#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define SIZE 30 
  
// Zamień wszystkie znaki ciągu
// na małe litery
void toLowerCase(char plain[], int ps) 
{ 
    int i; 
    for (i = 0; i < ps; i++) { 
        if (plain[i] > 64 && plain[i] < 91) 
            plain[i] += 32; 
    } 
} 
  
// Usuwanie wszystkich spacji w ciągu
int removeSpaces(char* plain, int ps) 
{ 
    int i, count = 0; 
    for (i = 0; i < ps; i++) 
        if (plain[i] != ' ') 
            plain[count++] = plain[i]; 
    plain[count] = '\0'; 
    return count; 
} 
  
// generuje kwadrat klucza 5x5
void generateKeyTable(char key[], int ks, 
                      char keyT[5][5]) 
{ 
    int i, j, k, flag = 0, *dicty; 
  
    // 26-znakowy hashmap
    // do przechowywania liczby alfabetu
    dicty = (int*)calloc(26, sizeof(int)); 
  
    for (i = 0; i < ks; i++) { 
        if (key[i] != 'j') 
            dicty[key[i] - 97] = 2; 
    } 
    dicty['j' - 97] = 1; 
  
    i = 0; 
    j = 0; 
    for (k = 0; k < ks; k++) { 
        if (dicty[key[k] - 97] == 2) { 
            dicty[key[k] - 97] -= 1; 
            keyT[i][j] = key[k]; 
            j++; 
            if (j == 5) { 
                i++; 
                j = 0; 
            } 
        } 
    } 
    for (k = 0; k < 26; k++) { 
        if (dicty[k] == 0) { 
            keyT[i][j] = (char)(k + 97); 
            j++; 
            if (j == 5) { 
                i++; 
                j = 0; 
            } 
        } 
    } 
} 
  
// Wyszukaj znaki dwuznaku w kluczowym kwadracie
// zwróć ich pozycję
void search(char keyT[5][5], char a, 
            char b, int arr[]) 
{ 
    int i, j; 
  
    if (a == 'j') 
        a = 'i'; 
    else if (b == 'j') 
        b = 'i'; 
  
    for (i = 0; i < 5; i++) { 
        for (j = 0; j < 5; j++) { 
            if (keyT[i][j] == a) { 
                arr[0] = i; 
                arr[1] = j; 
            } 
            else if (keyT[i][j] == b) { 
                arr[2] = i; 
                arr[3] = j; 
            } 
        } 
    } 
} 
  
// Funkcja znajdowania modułu z 5
int mod5(int a) 
{ 
    return (a % 5); 
} 
int prepare(char str[], int ptrs) 
{ 
    if (ptrs % 2 != 0) { 
        str[ptrs++] = 'z'; 
        str[ptrs] = '\0'; 
    } 
    return ptrs; 
} 

  
// Funkcja do odszyfrowania
void decrypt(char str[], char keyT[5][5], int ps) 
{ 
    int i, a[4]; 
    for (i = 0; i < ps; i += 2) { 
        search(keyT, str[i], str[i + 1], a); 
        if (a[0] == a[2]) { 
            str[i] = keyT[a[0]][mod5(a[1] - 1)]; 
            str[i + 1] = keyT[a[0]][mod5(a[3] - 1)]; 
        } 
        else if (a[1] == a[3]) { 
            str[i] = keyT[mod5(a[0] - 1)][a[1]]; 
            str[i + 1] = keyT[mod5(a[2] - 1)][a[1]]; 
        } 
        else { 
            str[i] = keyT[a[0]][a[3]]; 
            str[i + 1] = keyT[a[2]][a[1]]; 
        } 
    } 
} 
  
// Funkcja do wywołania odszyfrowania
void decryptByPlayfairCipher(char str[], char key[]) 
{ 
    char ps, ks, keyT[5][5]; 
  
    // Key 
    ks = strlen(key); 
    ks = removeSpaces(key, ks); 
    toLowerCase(key, ks); 
  
    // ciphertext 
    ps = strlen(str); 
    toLowerCase(str, ps); 
    ps = removeSpaces(str, ps); 
  
    generateKeyTable(key, ks, keyT); 
  
    decrypt(str, keyT, ps); 
} 
  
  
  
  void encrypt(char str[], char keyT[5][5], int ps) 
{ 
    int i, a[4]; 
  
    for (i = 0; i < ps; i += 2) { 
  
        search(keyT, str[i], str[i + 1], a); 
  
        if (a[0] == a[2]) { 
            str[i] = keyT[a[0]][mod5(a[1] + 1)]; 
            str[i + 1] = keyT[a[0]][mod5(a[3] + 1)]; 
        } 
        else if (a[1] == a[3]) { 
            str[i] = keyT[mod5(a[0] + 1)][a[1]]; 
            str[i + 1] = keyT[mod5(a[2] + 1)][a[1]]; 
        } 
        else { 
            str[i] = keyT[a[0]][a[3]]; 
            str[i + 1] = keyT[a[2]][a[1]]; 
        } 
    } 
} 
  
// Funkcja do szyfrowania za pomocą Playfair Cipher
void encryptByPlayfairCipher(char str[], char key[]) 
{ 
    char ps, ks, keyT[5][5]; 
  
    // Key 
    ks = strlen(key); 
    ks = removeSpaces(key, ks); 
    toLowerCase(key, ks); 
  
    // Plaintext 
    ps = strlen(str); 
    toLowerCase(str, ps); 
    ps = removeSpaces(str, ps); 
  
    ps = prepare(str, ps); 
  
    generateKeyTable(key, ks, keyT); 
  
    encrypt(str, keyT, ps); 
} 

// Główna funkcja
int main() 
{ 
printf( "PROGRAMN SLUZACY DO SZYFROWANIA I ODSZYFROWYWANIA ZA POMOCA SZYFRU Playfair \n  \n" );

    char str[SIZE], key[SIZE]; 
    
//FILE *plik = fopen("kryptogram.txt", "r");

 /* if (plik == NULL)    // otwarcie nie powiodło się
{
    printf("Otwarcie nieudane");
    exit(-1);    // trzeba dołączyć <stdlib.h>
}*/


//while (fscanf(plik, "%s", str) != EOF)
//fclose(plik);
  
    // Klucz do zaszyfrowania
     printf( "Podaj klucz do szyfrowania \n" );
   scanf( "%s", & key );
   // strcpy(key, "Monarchy"); 
    printf("Klucz tekstu: %s\n", key); 
    
     printf( "Wciśnij 1 aby zaszyfrować tekst lub 2 aby odszyfrować tekst \n" );
     
     int wybor;
  scanf( "%d", & wybor );
   if(wybor==1){
   	
   	// Zwykły tekst do zaszyfrowania
    //strcpy(str, "instruments"); 
    printf( "Podaj tekst, który ma zostać zaszyfrowany \n" );
     scanf( "%s", & str );
    printf("Zwykły tekst: %s\n", str); 
  
    // zaszyfruj za pomocą Playfair Cipher
    encryptByPlayfairCipher(str, key); 
  
    printf("Szyfrowany tekst: %s\n", str); 
}
printf( "Wciśnij 2 aby odszyfrować tekst lub enter aby wyjsc \n" );
       scanf( "%d", & wybor );

 if(wybor==2){
  
   /* // Zaszyfrowany tekst do odszyfrowania
    strcpy(str, "gatlmzclrqtx"); 
    printf("Zwykły tekst: %s\n", str); 
  */
    // Odszyfruj za pomocą Playfair Cipher
    decryptByPlayfairCipher(str, key); 
  
    printf("Odszyfrowany tekst: %s \n", str); 
}
  
    return 0; 
} 
  
