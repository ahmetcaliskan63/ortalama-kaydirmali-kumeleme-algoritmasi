#include <stdio.h>
#include <math.h>

#define VERI_SAYISI 5
#define BOYUT 2

double veri[VERI_SAYISI][BOYUT];
double merkez[VERI_SAYISI][BOYUT];

double kernel(double x) {
    return exp(-x * x / 2) / sqrt(2 * M_PI);
}

void kaydir(double *x, double *y) {
    double toplam[BOYUT] = {0};
    double normallestirme = 0;
    int k,d;
    for ( k = 0; k < VERI_SAYISI; k++) {
        double mesafe = 0;
        for ( d = 0; d < BOYUT; d++) {
            mesafe += (x[d] - veri[k][d]) * (x[d] - veri[k][d]);
        }
        double agirlik = kernel(sqrt(mesafe));

        normallestirme += agirlik;
        for (d = 0; d < BOYUT; d++) {
            toplam[d] += agirlik * veri[k][d];
        }
    }
    for ( d = 0; d < BOYUT; d++) {
        y[d] = toplam[d] / normallestirme;
    }
}

int main() {
    // Veri okuma
    int k,d;
    for ( k = 0; k< VERI_SAYISI; k++) {
        for ( d = 0; d < BOYUT; d++) {
            scanf("%lf", &veri[k][d]);
            merkez[k][d] = veri[k][d];
        }
    }

    // Ortalama kaydýrma
    for ( k = 0; k < VERI_SAYISI; k++) {
        double onceki[BOYUT];
        do {
            for ( d = 0; d < BOYUT; d++) {
                onceki[d] = merkez[k][d];
            }
            kaydir(merkez[k], merkez[k]);
        } while (fabs(merkez[k][0] - onceki[0]) > 1e-6 || fabs(merkez[k][1] - onceki[1]) > 1e-6);
    }

    // Sonuçlarý yazdýrma
    for (k = 0; k < VERI_SAYISI; k++) {
        printf("%d: (%lf, %lf)\n", k+1, merkez[k][0], merkez[k][1]);
    }

    return 0;
}
