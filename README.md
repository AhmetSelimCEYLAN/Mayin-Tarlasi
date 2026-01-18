# Mayın Tarlası (Terminal)

Bu proje, **C++** kullanılarak yazılmış ve **terminal üzerinden oynanan** bir Mayın Tarlası oyunudur.  
Amaç; klasik Minesweeper mantığını öğrenme odaklı, sade bir yapıyla sıfırdan implemente etmekti.

## Özellikler

- Terminal üzerinden oynanır (UI yok)
- Dinamik tahta boyutu (max 50x50)
- İlk tıklanan hücre ve çevresi **güvenli**
- Mayın yerleştirme
- Komşu mayın sayısı (`adj`) hesaplama
- Bayrak koyma (`flag`)
- Hücre açma (`bomb`)
- Kazanma ve kaybetme kontrolü

## Oynanış

Oyun başladığında:
1. Tahta boyutu (en, boy) ve mayın sayısı girilir
2. İlk hamle koordinat girilerek yapılır
3. Sonrasında her turda:
   - `B x y` → hücre aç (bomb)
   - `F x y` → bayrak koy / kaldır (flag)

Koordinatlar:
- Üstte görünen indeksler **sütun (x)**
- Solda görünen indeksler **satır (y)** olacak şekilde çalışır

## Teknik Notlar

- Tahta 1D `vector<Cell>` olarak tutulur  
  (`index = row * len + col`)
- Komşu hücre hesaplamaları `(row, col)` üzerinden yapılır
- Rastgelelik için `rand()` ve `std::random_shuffle` kullanılmıştır  
  (eski compiler uyumluluğu sebebiyle)

## ChatGPT Hakkında

Bu projede **ChatGPT’den yardım aldım**:
- Genel fikir geliştirme
- Algoritma yaklaşımı tartışmaları
- Bazı fonksiyonların yazımında

## Bilinen Kısıtlar

- Terminal UI sade tutulmuştur
- Grafik arayüz (UI) yok
- Bazı edge-case’ler bilinçli olarak ele alınmamıştır

## Neden Böyle?

Bu proje:
- “Mükemmel olsun” diye değil
- **“Bitmiş, çalışan ve öğretici olsun”** diye yazıldı

Eğer ileride bir UI eklersem (belki birkaç sene sonra 🙂),  
o zaman daha temiz bir mimari ve ek mekanikler de eklenebilir.

## Derleme

Basitçe:

```bash
g++ main.cpp mayin_tarlasi.cpp -o mayin
