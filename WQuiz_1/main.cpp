#include <cstdio>
#define MSTR 21

bool wcMatch(char s[], char p[], int n, int m);

int main() {
    char s[MSTR]; // a text input without wildcards.
    char p[MSTR]; // a text input with wildcards.
    char line[MSTR + MSTR]; // a line of the input file
    FILE *f = fopen("input.txt", "r"); 
    if (f) { 
        while(fgets(line, MSTR*2, f) != NULL) { 
            sscanf(line, "%s%s", s, p); 
            printf("%s,%s->", s, p); 
            int n, m, u; // n for a length of s, m for a length of p
            for (u = 0; s[u] != '\0'; u++); n = u; 
            for (u = 0; p[u] != '\0'; u++); m = u; 
            bool ret = wcMatch(s, p, n, m); 
            printf(" matching?  %s \n",  ret? "true": "false"); 
        } 
    } 
  return 0; 
} 

bool wcMatch(char s[], char p[], int n, int m)
{
    printf("%s,", p);
    // Leave only one asterisk if there are a series of asterisks in the pattern
    int n_ast = 0, j = 0, u;
    while (j <= n)
    {
        p[j - n_ast] = p[j];
        ++j;
        if (p[j] == '*')
        {
            ++j;
            while(p[j] == '*') ++j, ++n_ast;
        }
    }
    for (u = 0; p[u] != '\0'; u++); m = u;

    // Create 2D array for Dynamic Programming
    bool** DP = new bool*[n + 1];
    for (int idx = 0; idx < n + 1; idx++) 
    { 
        DP[idx] = new bool[m + 1];
        for (int k = 0; k < m + 1; k++) DP[idx][k] = false;
    }

    DP[0][0] = true;
    for (int j = 1; j <= m; j++)
    {
        if (p[j - 1] == '*')
        {
            int true_idx = 0;
            for(; true_idx <= n && DP[true_idx][j-1] != true; true_idx++);
            for (int i = true_idx; i <= n; i++) DP[i][j] = true;
        }
        else
        {
            for (int i = 1; i <= n; i++)
            {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '?')
                {
                    DP[i][j] = DP[i - 1][j - 1];
                }
            }
        }
    }
    bool result = DP[n][m];

    // Delete the array
    for (int idx = 0; idx <= n; idx++) delete DP[idx];
    delete DP;

    return result;
}