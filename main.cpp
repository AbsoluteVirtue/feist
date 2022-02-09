#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *
    encipher(
        char * result,
        const char * text,
        const char * key,
        const size_t len)
{
    size_t pivot = len % 2 ? (len / 2) + 1 : len / 2;
    char k1 [pivot] {0};
    memcpy(k1, key, pivot);

    char k2 [pivot] {0};
    memcpy(k2, key + pivot, len - pivot);

    char l1 [pivot] {0};
    memcpy(l1, text, pivot);
    char r1 [pivot] {0};
    memcpy(r1, text + pivot, len - pivot);

    char f1 [pivot] {0};
    for (size_t i = 0; i < pivot; i++)
    {
        f1[i] = k1[i] ^ r1[i];
    }

    char r2[pivot] {0};
    for (size_t i = 0; i < pivot; i++)
    {
        r2[i] = f1[i] ^ l1[i];
    }

    char l2[pivot] {0};
    memcpy(l2, r1, pivot);

    char f2[pivot] {0};
    for (size_t i = 0; i < pivot; i++)
    {
        f2[i] = r2[i] ^ k2[i];
    }

    char r3[pivot] {0};
    for (size_t i = 0; i < pivot; i++)
    {
        r3[i] = f2[i] ^ l2[i];
    }

    char l3[pivot] {0};
    memcpy(l3, r2, pivot);

    memcpy(result, l3, pivot);
    memcpy(result + pivot, r3, pivot);

    return result;
}

char *
    decipher(
        char * result,
        const char * ciphertext,
        const char * key,
        const size_t len)
{
    size_t pivot = len % 2 ? (len / 2) + 1 : len / 2;
    char k1 [pivot] {0};
    memcpy(k1, key, pivot);

    char k2 [pivot] {0};
    memcpy(k2, key + pivot, len - pivot);

    char l4 [pivot] {0};
    memcpy(l4, ciphertext, pivot);

    char r4 [pivot] {0};
    memcpy(r4, ciphertext + pivot, (len % 2 ? len + 1 : len) - pivot);

    char f3 [pivot] {0};
    for (size_t i = 0; i < pivot; i++)
    {
        f3[i] = k2[i] ^ l4[i];
    }

    char l5 [pivot] {0};
    for (size_t i = 0; i < pivot; i++)
    {
        l5[i] = f3[i] ^ r4[i];
    }

    char r5 [pivot] {0};
    memcpy(r5, l4, pivot);

    char f4 [pivot] {0};
    for (size_t i = 0; i < pivot; i++)
    {
        f4[i] = k1[i] ^ l5[i];
    }

    char l6 [pivot] {0};
    for (size_t i = 0; i < pivot; i++)
    {
        l6[i] = f4[i] ^ r5[i];
    }

    char r6 [pivot] {0};
    memcpy(r6, l5, pivot);

    memcpy(result, l6, pivot);
    memcpy(result + pivot, r6, pivot);

    return result;
}

int main(int argc, char const *argv[])
{
    char plaintext [100] {0};
    char ciphertext [100] {0};
    char result [100] {0};

    // Argument parsing goes here
    if (argc > 1) 
    {
        strcpy(plaintext, argv[1]);
    } 
    else 
    {
        // default value for testing purposes
        strcpy(
            plaintext,
            "Test sentence with spaces and capital letters, that is also very long.");
    }

    const size_t n = strlen(plaintext);
    char key [n];
    if (argc > 2)
    {
        memcpy(key, argv[2], n);
    }
    else
    {
        // default value for testing purposes
        srand(777);
        for (size_t i = 0; i < n; i++)
        {
            key[i] = rand() % 10;
        }
    }

    printf("%s\n", plaintext);
    printf("%s\n", encipher(ciphertext, plaintext, key, n));
    printf("%s\n", decipher(result, ciphertext, key, n));
}
