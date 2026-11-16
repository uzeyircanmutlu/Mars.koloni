# Mars Kolonisi Yaşam Destek Simülatörü

Algoritma ve Programlama dersi kapsamında **ANSI C (C89)** standartlarına uygun olarak geliştirilmiş, metin tabanlı bir hayatta kalma ve kaynak yönetimi simülasyonudur. Oyuncu, Mars'taki bir araştırma istasyonunda tek başına kalan bir mühendisi yöneterek kurtarma ekibi gelene kadar **15 gün** boyunca hayatta kalmaya çalışır.

## Temel Özellikler

* **Zorluk Seviyeleri:** Kolay (`K`), Normal (`N`) ve Zor (`Z`) seçeneklerine göre değişen başlangıç kaynakları, fırtına süreleri ve olay eşikleri.
* **Zaman Akışı:** Geçerli her komut 1 tur harcar (`D` komutu ve tanımsız girişler hariç). Her 3 turda bir yeni güne geçilir ve günlük oksijen tüketimi gerçekleşir.
* **Olasılık Sistemi:** `srand(time(NULL))` ve `rand() % 100` tabanlı zar-eşik karşılaştırmaları.
* **Dinamik Şifreleme:** Bulunulan gün sayısına göre ASCII tablosu üzerinden aritmetik olarak türetilen (`'A' + (gun % 26)`) hava kilidi şifreleme mekanizması.

## Komut Listesi

| Komut | İşlev | Açıklama |
| :---: | :--- | :--- |
| **`G` / `g`** | Keşif Görevi | Enerji (-15) ve oksijen (-10) harcar. Su veya yedek parça bulma ihtimalini değerlendirir. |
| **`O` / `o`** | Oksijen Üretimi | Elektroliz ile her 2 birim suyu 3 birim oksijene dönüştürür (-10 Enerji). |
| **`T` / `t`** | Modül Tamiri | Hasar kademesine göre (Hafif / Orta / Ağır) yedek parça harcayarak modül hasarını azaltır. |
| **`D` / `d`** | Durum Raporu | Tur harcamadan tüm istasyon verilerini ve kritik sistem uyarılarını listeler. |
| **`U` / `u`** | Uyu / Dinlen | Enerji (+30) ve sağlık (+15) kazandırır. Oksijen 20'nin altındaysa sağlık kaybı yaşanır. |
| **`K` / `k`** | Kum Fırtınası | Zorluk seviyesine göre belirlenen tur sayısınca fırtına simülasyonunu çalıştırır. |
| **`H` / `h`** | Hava Kilidi | 3 deneme hakkıyla doğru harf şifresini bularak hava kilidini fırtınalara karşı mühürler. |
| **`Q` / `q`** | Çıkış | Simülasyonu sonlandırır ve sonuç raporunu ekrana yazdırır. |

## Derleme ve Çalıştırma

```bash
gcc main.c -o mars_simulator -ansi -pedantic -Wall
./mars_simulator
```

## Puanlama Formülü

```text
Puan = (Gün x 100) + Sağlık + Oksijen - Modül Hasarı
```
