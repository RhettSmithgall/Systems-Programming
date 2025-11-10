#include "headers.h"


// Function to find LCS length between two strings
int lcs(const char *a, const char *b) {
    int n = strlen(a);
    int m = strlen(b);
    int **dp = malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++)
        dp[i] = calloc(m + 1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
        }
    }

    int result = dp[n][m];

    for (int i = 0; i <= n; i++)
        free(dp[i]);
    free(dp);

    return result;
}

// Returns pointer to list entry with longest common subsequence
struct symbol *spellchecker(const char *target,struct symbol *head) {
    struct symbol *best = NULL;
    int best_score = -1;

    for (struct symbol *cur = head; cur != NULL; cur = cur->next) {
        int score = lcs(target, cur->name);
        if (score > best_score) {
            best_score = score;
            best = cur;
        }
    }

    return best;
}
