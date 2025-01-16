# Fruit Ninja Benzeri Oyun (Qt C++)

Bu proje, **Qt Framework** kullanılarak geliştirilmiş bir **Fruit Ninja** tarzı oyundur. Oyuncular, ekrandaki karpuzları keserek puan kazanırken bombalardan kaçmak zorundadır. Proje, C++ dilinde yazılmıştır ve eğitici bir oyun projesi olarak tasarlanmıştır.

## 📝 Özellikler

- **Karpuz Kesme Mekanizması:**
  - Ekrandaki karpuzlara tıklayarak puan kazanılır.
  - Karpuzların rastgele yerlerde oluşturulması ve hareket etmesi.
- **Bomba ve Hediye Mekanizması:**
  - Bombalara tıklandığında puan azalır.
  - Belirli aralıklarla bonus kutuları düşer:
    - +5 saniye ekleme
    - -5 saniye azaltma
    - Ekrandaki tüm karpuzları kesme
- **Skor Takibi:**
  - Oyun sırasında en yüksek skor ve kaçırılan karpuz sayısı görüntülenir.
  - Oyun sonunda skor bilgileri kaydedilir.

## 📂 Proje Dosyaları

- `main.cpp`: Uygulamanın başlangıç noktası.
- `dialog.cpp` & `dialog.h`: Oyunun ana mantığı ve kullanıcı arayüzü işlevlerini içerir.
- `MyLabel.h`: Tıklama olaylarını algılayan özel QLabel sınıfı.
- `dialog.ui`: Kullanıcı arayüzü tasarımı.
- `Resources.qrc`: Görsellerin ve diğer kaynakların tanımlandığı dosya.
- `.pro` ve `.pro.user`: Qt projesi ayar dosyaları.

## 🚀 Çalıştırma Talimatları

### Gereksinimler
- Qt Framework (6.6.2 veya uyumlu bir sürüm)
- MinGW veya diğer bir uygun derleyici

### Adımlar
1. Proje dosyalarını Qt Creator ile açın (`.pro` dosyasını seçin).
2. Projeyi `Build` edin.
3. Uygulamayı çalıştırmak için `Run` butonuna tıklayın.

## 🖼️ Ekran Görüntüleri

1. **Oyun Ekranı:**
   - Karşılaşacağınız arayüz.
2. **Oyun Bitişi:**
   - Skor tablosunun yer aldığı mesaj kutusu.

## 💡 Kullanılan Teknolojiler

- **Programlama Dili:** C++
- **Framework:** Qt
- **IDE:** Qt Creator
