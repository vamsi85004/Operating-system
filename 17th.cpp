int allocate[P][R] = { { 0, 1, 0 },  // P0 
                       { 2, 0, 0 },  // P1 
                       { 3, 0, 2 },  // P2 
                       { 2, 1, 1 },  // P3 
                       { 0, 0, 2 } }; // P4

int max[P][R] = { { 7, 5, 3 },  // P0
                  { 3, 2, 2 },  // P1
                  { 9, 0, 2 },  // P2
                  { 2, 2, 2 },  // P3
                  { 4, 3, 3 } }; // P4

int avail[R] = { 3, 3, 2 };  // Available resources

void calculateNeed(int need[P][R]) {
    for (int i = 0 ; i < P ; i++)
        for (int j = 0 ; j < R ; j++)
            need[i][j] = max[i][j] - allocate[i][j];
}

bool isSafe() {
    int need[P][R];
    calculateNeed(need);

    bool finish[P] = {0};
    int safeSeq[P];
    int work[R];

    for (int i = 0; i < R ; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == R) {
                    for (int k = 0 ; k < R ; k++)
                        work[k] += allocate[p][k];

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }

        if (found == false) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P ; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");

    return true;
}

int main() {
    isSafe();
    return 0;
}
