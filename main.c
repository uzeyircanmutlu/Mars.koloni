#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int saglik = 100, enerji = 100, oksijen = 100, su, yedekParca, modulHasari, kilitMuhurlu = 0, gun = 1, tur = 0;
    int zorlukGecerli = 0, firtinaSuresi, firtinaEsik, kesifTabanEsik, turHarca, oyunBitti = 0, zar, esik, yaralanmaZari;
    int girilenSu, harcananSu, artikSu, uretilenOksijen, i, ruzgarCarpani, hasarliTurSayisi, toplamSaglikKaybi, toplamOksijenKaybi;
    int anlikSaglikKaybi, anlikOksijenKaybi, anlikHasarArtisi, denemeHakki, puan, raporGun;
    char zorluk, komut, dogruSifre, girilenSifre;

    srand((unsigned int)time(NULL));

    printf("====================================================\n");
    printf("   MARS KOLONISI YASAM DESTEK SIMULATORU (15 GUN)   \n");
    printf("====================================================\n\n");

    do {
        printf("Zorluk seviyesi seciniz (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &zorluk);

        switch (zorluk) {
            case 'k': case 'K':
                su = 12; yedekParca = 5; modulHasari = 10; firtinaSuresi = 3; firtinaEsik = 40; kesifTabanEsik = 50; zorlukGecerli = 1;
                printf("\n[SISTEM] Kolay zorluk secildi. Baslangic kaynaklari bol.\n");
                break;
            case 'n': case 'N':
                su = 8; yedekParca = 3; modulHasari = 25; firtinaSuresi = 5; firtinaEsik = 55; kesifTabanEsik = 40; zorlukGecerli = 1;
                printf("\n[SISTEM] Normal zorluk secildi. Standart protokol aktif.\n");
                break;
            case 'z': case 'Z':
                su = 5; yedekParca = 2; modulHasari = 45; firtinaSuresi = 7; firtinaEsik = 70; kesifTabanEsik = 30; zorlukGecerli = 1;
                printf("\n[SISTEM] Zor seviye secildi! Kaynaklar kit, firtinalar siddetli.\n");
                break;
            default:
                printf("[UYARI] Gecersiz zorluk seviyesi! Lutfen K, N veya Z giriniz.\n\n");
                zorlukGecerli = 0;
                break;
        }
    } while (!zorlukGecerli);

    do {
        turHarca = 0;

        printf("\n----------------------------------------------------\n");
        printf("[GUN: %d/15 | TUR: %d] Saglik:%d | Enerji:%d | Oksijen:%d | Su:%d | Parca:%d | Hasar:%d | Kilit:%s\n",
               gun, tur, saglik, enerji, oksijen, su, yedekParca, modulHasari,
               (kilitMuhurlu == 1) ? "MUHURLU" : "ACIK");
        printf("Komutlar: [G]Kesif [O]Oksijen [T]Tamir [D]Durum [U]Uyu [K]Firtina [H]HavaKilidi [Q]Cikis\n");
        printf("Komutunuz: ");
        scanf(" %c", &komut);

        switch (komut) {
            case 'g': case 'G':
                if (enerji < 15) {
                    printf("[IPTAL] Kesif gorevi icin yeterli enerjiniz yok! (Gereken: 15, Mevcut: %d)\n", enerji);
                } else {
                    printf("\n>>> KESIF GOREVI BASLADI <<<\n");
                    enerji -= 15; oksijen -= 10; turHarca = 1;
                    esik = (enerji > 40 && oksijen > 30) ? kesifTabanEsik + 30 : kesifTabanEsik;
                    zar = rand() % 100;
                    printf("[KESIF ZARI] Zar: %d / Esik: %d -> ", zar, esik);
                    if (zar < (esik / 2)) {
                        printf("BASARILI! Yeralti buzulu tespit edildi (+4 Birim Su).\n");
                        su += 4;
                    } else if (zar < esik) {
                        printf("BASARILI! Eski kesif aracindan parca sokuldu (+2 Yedek Parca).\n");
                        yedekParca += 2;
                    } else {
                        printf("BASARISIZ! Kesif alanindan eli bos donuldu.\n");
                    }

                    yaralanmaZari = rand() % 100;
                    printf("[TEHLIKE ZARI] Zar: %d / Esik: 10 (veya Modul Hasari > 70 [Mevcut: %d]) -> ", yaralanmaZari, modulHasari);
                    if (yaralanmaZari < 10 || modulHasari > 70) {
                        printf("YARALANMA! Kesif sirasinda kaza gecirdiniz (-15 Saglik).\n");
                        saglik -= 15;
                    } else {
                        printf("GUVENLI. Herhangi bir yaralanma yasanmadi.\n");
                    }
                }
                break;

            case 'o': case 'O':
                if (enerji < 10) {
                    printf("[IPTAL] Elektroliz islemi icin yeterli enerjiniz yok! (Gereken: 10, Mevcut: %d)\n", enerji);
                } else if (su < 2) {
                    printf("[IPTAL] Oksijen uretimi icin en az 2 birim su gereklidir! (Mevcut Su: %d)\n", su);
                } else {
                    printf("\n>>> OKSIJEN URETIM UNITESI <<<\n");
                    printf("Kac birim su kullanmak istiyorsunuz? (Mevcut Su: %d): ", su);
                    scanf("%d", &girilenSu);

                    if (girilenSu > su) {
                        printf("[IPTAL] Depodaki mevcut sudan (%d) fazla miktar giremezsiniz!\n", su);
                    } else if (girilenSu < 2) {
                        printf("[IPTAL] Donusum icin en az 2 birim su girmelisiniz!\n");
                    } else {
                        artikSu = girilenSu % 2;
                        harcananSu = girilenSu - artikSu;
                        uretilenOksijen = (harcananSu / 2) * 3;
                        su -= harcananSu; enerji -= 10; oksijen += uretilenOksijen; turHarca = 1;
                        printf("[URETIM] %d birim su kullanildi (%d birim tek oldugu icin depoda artik kaldi).\n", harcananSu, artikSu);
                        printf("[URETIM] +%d birim oksijen uretildi, -10 enerji harcandi.\n", uretilenOksijen);
                    }
                }
                break;

            case 't': case 'T':
                if (yedekParca <= 0) {
                    printf("[IPTAL] Yedek parcaniz yok! Tamir yapilamaz.\n");
                } else if (enerji < 10) {
                    printf("[IPTAL] Tamir icin yeterli enerjiniz yok! (Gereken: 10, Mevcut: %d)\n", enerji);
                } else if (modulHasari == 0) {
                    printf("[IPTAL] Istasyon modullerinde herhangi bir hasar bulunmuyor.\n");
                } else {
                    printf("\n>>> MODUL TAMIR ISLEMI <<<\n");
                    if (modulHasari <= 30) {
                        yedekParca--; modulHasari -= 15; enerji -= 10; turHarca = 1;
                        printf("[TAMIR - HAFIF HASAR] 1 yedek parca ve 10 enerji harcandi. Hasar 15 birim azaltildi.\n");
                    } else if (modulHasari <= 70) {
                        if (yedekParca >= 2) {
                            yedekParca -= 2; modulHasari -= 35; enerji -= 10; turHarca = 1;
                            printf("[TAMIR - ORTA HASAR] 2 yedek parca ve 10 enerji harcandi. Hasar 35 birim azaltildi.\n");
                        } else {
                            printf("[IPTAL] Orta seviye hasar onarimi icin en az 2 yedek parca gereklidir! (Mevcut: %d)\n", yedekParca);
                        }
                    } else {
                        if (yedekParca >= 3) {
                            yedekParca -= 3; modulHasari -= 55; enerji -= 10; turHarca = 1;
                            printf("[TAMIR - AGIR HASAR] 3 yedek parca ve 10 enerji harcandi. Hasar 55 birim azaltildi.\n");
                        } else {
                            printf("[IPTAL] Agir seviye hasar onarimi icin en az 3 yedek parca gereklidir! (Mevcut: %d)\n", yedekParca);
                        }
                    }
                }
                break;

            case 'd': case 'D':
                printf("\n================ ISTASYON DURUM RAPORU ================\n");
                printf("Gun           : %d / 15\n", gun);
                printf("Toplam Tur    : %d\n", tur);
                printf("Saglik        : %d / 100\n", saglik);
                printf("Enerji        : %d / 100\n", enerji);
                printf("Oksijen       : %d / 100\n", oksijen);
                printf("Su Miktari    : %d birim\n", su);
                printf("Yedek Parca   : %d adet\n", yedekParca);
                printf("Modul Hasari  : %d / 100\n", modulHasari);
                printf("Hava Kilidi   : %s\n", (kilitMuhurlu == 1) ? "Muhurlu (Guvenli)" : "Acik (Riskli)");
                printf("-------------------------------------------------------\n");

                if (oksijen < 25) printf("[KRITIK UYARI] Oksijen seviyesi cok dusuk (%d)! Acilen oksijen uretin (O).\n", oksijen);
                if (saglik < 30) printf("[KRITIK UYARI] Saglik durumu tehlikede (%d)! Dinlenmeniz gerekiyor (U).\n", saglik);
                if (modulHasari > 70) printf("[KRITIK UYARI] Modul hasari kritik seviyede (%d)! Modulleri onarin (T).\n", modulHasari);
                if (enerji < 20) printf("[KRITIK UYARI] Enerji tukenmek uzere (%d)! Dinlenmeye gecin (U).\n", enerji);
                if (su < 4) printf("[KRITIK UYARI] Su rezervleri azaliyor (%d)! Kesif gorevine cikin (G).\n", su);

                if (oksijen >= 25 && saglik >= 30 && modulHasari <= 70 && enerji >= 20 && su >= 4) {
                    printf("[BILGI] TUM SISTEMLER NORMAL.\n");
                }
                printf("=======================================================\n");
                break;

            case 'u': case 'U':
                printf("\n>>> DINLENME MODU <<<\n");
                enerji += 30; oksijen -= 6; turHarca = 1;
                if (oksijen < 20) {
                    saglik -= 12;
                    printf("[UYARI] Kabin ici oksijen 20'nin altinda (%d)! Uyurken bogulma tehlikesi gecirdiniz (-12 Saglik, +30 Enerji).\n", oksijen);
                } else {
                    saglik += 15;
                    printf("[DINLENME] Verimli bir uyku uyudunuz (+15 Saglik, +30 Enerji, -6 Oksijen).\n");
                }
                break;

            case 'k': case 'K':
                if (enerji < 10) {
                    printf("[IPTAL] Firtina protokollerini yonetmek icin en az 10 enerji gereklidir! (Mevcut: %d)\n", enerji);
                } else {
                    printf("\n>>> KUM FIRTINASI SIMULASYONU BASLADI (%d Tur) <<<\n", firtinaSuresi);
                    enerji -= 10; turHarca = 1; hasarliTurSayisi = 0; toplamSaglikKaybi = 0; toplamOksijenKaybi = 0;

                    for (i = 1; i <= firtinaSuresi; i++) {
                        ruzgarCarpani = (i % 2 == 0) ? 2 : 1;
                        printf("\n[Firtina Tur %d/%d - %s Ruzgar] ", i, firtinaSuresi, (ruzgarCarpani == 2) ? "SIDDETLI (2x)" : "Normal (1x)");
                        
                        zar = rand() % 100;
                        printf("Zar: %d / Esik: %d -> ", zar, firtinaEsik);

                        if (zar < 25) {
                            if (kilitMuhurlu == 1) {
                                printf("OKSIJEN SIZINTISI ENGELLENDI! (Hava kilidi muhurlu oldugu icin bu tur atlandi).\n");
                                continue;
                            }
                            anlikOksijenKaybi = 7 * ruzgarCarpani;
                            oksijen -= anlikOksijenKaybi;
                            toplamOksijenKaybi += anlikOksijenKaybi;
                            hasarliTurSayisi++;
                            printf("OKSIJEN SIZINTISI! -%d Oksijen kaybedildi.\n", anlikOksijenKaybi);
                        } else if (zar < firtinaEsik) {
                            anlikSaglikKaybi = 5 * ruzgarCarpani;
                            anlikHasarArtisi = 6 * ruzgarCarpani;
                            saglik -= anlikSaglikKaybi;
                            modulHasari += anlikHasarArtisi;
                            toplamSaglikKaybi += anlikSaglikKaybi;
                            hasarliTurSayisi++;
                            printf("HASAR ALINDI! (-%d Saglik, +%d Modul Hasari).\n", anlikSaglikKaybi, anlikHasarArtisi);
                        } else {
                            printf("BASARILI! Firtina dalgasindan zararsiz korundunuz.\n");
                        }

                        if (saglik < 0) saglik = 0;
                        if (oksijen < 0) oksijen = 0;
                        if (modulHasari > 100) modulHasari = 100;
                        if (saglik == 0 || oksijen == 0) {
                            printf("\n[ACIL DURUM] Firtina sirasinda hayati degerler 0'a dustu!\n");
                            break;
                        }
                    }
                    printf("\n--- KUM FIRTINASI OZETI ---\n");
                    printf("Hasar Alinan Tur Sayisi : %d / %d\n", hasarliTurSayisi, firtinaSuresi);
                    printf("Toplam Kaybedilen Saglik: %d\n", toplamSaglikKaybi);
                    printf("Toplam Kaybedilen Oksijen: %d\n", toplamOksijenKaybi);
                    printf("---------------------------\n");
                }
                break;

            case 'h': case 'H':
                if (enerji < 5) {
                    printf("[IPTAL] Hava kilidi konsolunu calistirmak icin en az 5 enerji gereklidir! (Mevcut: %d)\n", enerji);
                } else if (kilitMuhurlu == 1) {
                    printf("[BILGI] Hava kilidi zaten muhurlu durumda!\n");
                } else {
                    printf("\n>>> HAVA KILIDI SIFRE DOGULAMA SISTEMI <<<\n");
                    dogruSifre = (char)('A' + (gun % 26));
                    denemeHakki = 3; turHarca = 1;
                    printf("[IPUCU] Sifre, alfabede 'A' harfinden bugunun gun sayisinin 26'ya bolumunden kalan (%d) kadar ilerideki harftir.\n", gun % 26);

                    do {
                        printf("Kilit sifresini giriniz (Kalan Hak: %d): ", denemeHakki);
                        scanf(" %c", &girilenSifre);
                        if (girilenSifre >= 'a' && girilenSifre <= 'z') girilenSifre -= 32;

                        if (girilenSifre != dogruSifre) {
                            denemeHakki--; enerji -= 5;
                            if (enerji < 0) enerji = 0;
                            printf(girilenSifre < dogruSifre ? "[YANLIS] Enerji -5. Ipucu: Alfabede daha ILERI git!\n" : "[YANLIS] Enerji -5. Ipucu: Alfabede daha GERI git!\n");
                        }
                    } while (girilenSifre != dogruSifre && denemeHakki > 0);

                    if (girilenSifre == dogruSifre) {
                        kilitMuhurlu = 1;
                        printf("[BASARILI] Sifre dogrulandi (%c)! Hava kilidi muhurlendi.\n", dogruSifre);
                    } else {
                        modulHasari += 20;
                        printf("[BASARISIZ] Haklar bitti! Dogru sifre '%c' idi. Modul Hasari +20 artti.\n", dogruSifre);
                    }
                }
                break;

            case 'q': case 'Q':
                printf("\n[SISTEM] Simulasyondan cikis komutu alindi...\n");
                oyunBitti = 1;
                break;

            default:
                printf("[HATA] Tanimsiz komut girdiniz ('%c')! Bu islem tur/sure harcamaz.\n", komut);
                turHarca = 0;
                break;
        }

        if (saglik > 100) saglik = 100;
        if (saglik < 0) saglik = 0;
        if (enerji > 100) enerji = 100;
        if (enerji < 0) enerji = 0;
        if (oksijen > 100) oksijen = 100;
        if (oksijen < 0) oksijen = 0;
        if (modulHasari > 100) modulHasari = 100;
        if (modulHasari < 0) modulHasari = 0;

        if (turHarca && !oyunBitti) {
            tur++;
            if (saglik <= 0 || oksijen <= 0) {
                oyunBitti = 1;
            } else if (tur % 3 == 0) {
                gun++;
                if (gun <= 15) {
                    printf("\n****************************************************\n");
                    printf("   YENI GUN BASLADI: GUN %d (-8 Oksijen)\n", gun);
                    oksijen -= 8;
                    if (modulHasari > 70) {
                        printf("   Agir modul hasari nedeniyle radyasyon sizintisi: -5 Saglik!\n");
                        saglik -= 5;
                    }
                    printf("****************************************************\n");
                    if (oksijen < 0) oksijen = 0;
                    if (saglik < 0) saglik = 0;
                }
            }
        }

        if (saglik <= 0 || oksijen <= 0) {
            printf("\n====================================================\n");
            printf(saglik <= 0 ? "   OYUN BITTI: Sagliginiz tukendi!\n" : "   OYUN BITTI: Oksijen tukendi!\n");
            printf("====================================================\n");
            oyunBitti = 1;
        } else if (gun > 15) {
            printf("\n====================================================\n");
            printf("   TEBRIKLER! 15. GUNU TAMAMLADINIZ! Kurtuldunuz!\n");
            printf("====================================================\n");
            oyunBitti = 1;
        }

    } while (!oyunBitti);

    raporGun = (gun > 15) ? 15 : gun;
    puan = (raporGun * 100) + saglik + oksijen - modulHasari;

    printf("\n================ SIMULASYON SONUC RAPORU ================\n");
    printf("Sonuc Durumu          : %s\n", (gun > 15 && saglik > 0 && oksijen > 0) ? "KAZANDINIZ" : ((saglik <= 0 || oksijen <= 0) ? "KAYBETTINIZ" : "CIKIS YAPILDI"));
    printf("Hayatta Kalinan Gun   : %d\n", raporGun);
    printf("Toplam Gecen Tur      : %d\n", tur);
    printf("Son Saglik Degeri     : %d\n", saglik);
    printf("Son Enerji Degeri     : %d\n", enerji);
    printf("Son Oksijen Degeri    : %d\n", oksijen);
    printf("Son Su Miktari        : %d\n", su);
    printf("Son Yedek Parca Sayisi: %d\n", yedekParca);
    printf("Son Modul Hasari      : %d\n", modulHasari);
    printf("---------------------------------------------------------\n");
    printf("TOPLAM PUAN           : %d\n", puan);
    printf("=========================================================\n");

    return 0;
}
