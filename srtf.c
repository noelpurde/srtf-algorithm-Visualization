#include <stdio.h>
#include <stdbool.h>

#define MAX_Procese 100

typedef struct {
    int id;
    int k_mberritjes;
    int k_ekzekutimit;
    int k_qendrimit;
    int k_mbetur;
    int k_perfundimit;
    int k_pritjes;
} Proces;

void llogKohen(Proces p[], int n) {
    int k_aktuale = 0;
    int kompletuar = 0;
    bool flag = false;

    while (kompletuar != n) {
        int min_index = -1;
        int minimum = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].k_mberritjes <= k_aktuale && p[i].k_mbetur > 0) {
                if (p[i].k_mbetur < minimum) {
                    minimum = p[i].k_mbetur;
                    min_index = i;
                    flag = true;
                }
                if (p[i].k_mbetur == minimum) {
                    if (p[i].k_mberritjes < p[min_index].k_mberritjes) {
                        minimum = p[i].k_mbetur;
                        min_index = i;
                        flag = true;
                    }
                }
            }
        }

        if (!flag) {
            k_aktuale++;
        } else {
            p[min_index].k_mbetur--;
            k_aktuale++;
            if (p[min_index].k_mbetur == 0) {
                p[min_index].k_perfundimit = k_aktuale;
                p[min_index].k_pritjes = p[min_index].k_perfundimit - p[min_index].k_ekzekutimit - p[min_index].k_mberritjes;
                p[min_index].k_qendrimit = p[min_index].k_perfundimit - p[min_index].k_mberritjes;
                kompletuar++;
                flag = false;
            }
        }
    }
}

int main() {
    Proces p[MAX_Procese];
    int n;

    printf("Vendos numrin e proceseve: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Vendos kohen e mberritjes dhe kohen e ekzekutimit per Procesin %d: ", i + 1);
        scanf("%d %d", &p[i].k_mberritjes, &p[i].k_ekzekutimit);
        p[i].id = i + 1;
        p[i].k_mbetur = p[i].k_ekzekutimit;
    }

    llogKohen(p, n);

    printf("\nID\tK. Mberritjes\tK. Ekzekutimit\tK. Pritjes\tK. Qendrimit\tK. Kompletimit\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].k_mberritjes, p[i].k_ekzekutimit, p[i].k_pritjes, p[i].k_qendrimit, p[i].k_perfundimit);
    }

    return 0;
}
