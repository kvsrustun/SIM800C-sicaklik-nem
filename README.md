# 📲 SIM800C ile SMS Tabanlı Sıcaklık ve Nem Takip Sistemi

<p align="center">
  <img src="https://img.shields.io/badge/Donanım-Deneyap%20Kart%201A-007acc?style=for-the-badge&logo=espressif&logoColor=white" alt="Donanım" />
  <img src="https://img.shields.io/badge/GSM%20Modülü-SIM800C%20SMS-e11d48?style=for-the-badge" alt="GSM" />
  <img src="https://img.shields.io/badge/Sensör-Sıcaklık%20%26%20Nem-059669?style=for-the-badge" alt="Sensör" />
  <img src="https://img.shields.io/badge/Besleme-3.7V%202000mAh%20LiPo-f59e0b?style=for-the-badge" alt="Batarya" />
  <img src="https://img.shields.io/badge/Lisans-MIT-brightgreen?style=for-the-badge" alt="Lisans" />
</p>

> **Wi-Fi ve internet bağlantısının bulunmadığı ortamlarda;** Deneyap Kart 1A, I2C Sıcaklık/Nem Sensörü ve **SIM800C GSM Modülü** kullanılarak ortamın sıcaklık ve nem değerlerini doğrudan cep telefonuna **otonom SMS olarak gönderen** kablosuz IoT erken uyarı ve telemetri projesi.

---

<a id="icindekiler"></a>
## 📑 İçindekiler

1. [Proje Özeti ve Temel Amaç](#proje-ozeti)
2. [Devre Şeması ve Canlı SMS Gönderim Demosu](#devre-ve-demo)
3. [Kullanılan Donanımlar ve Modüller](#donanimlar)
4. [Pin Haritası ve Bağlantı Tablosu](#pin-haritasi)
5. [AT Komutları ile SMS İletişim Mantığı](#sms-mantigi)
6. [Kurulum ve Çalıştırma Rehberi](#kurulum-ve-calistirma)
7. [Karşılaşılabilecek Sorunlar ve Çözümleri](#sorunlar-ve-cozumleri)
8. [Geliştirici](#gelistirici)
9. [Lisans](#lisans)

---

<a id="proje-ozeti"></a>
## 🎯 1. Proje Özeti ve Temel Amaç

Tarım arazileri, seralar, izole depolar ve dağ evleri gibi internet altyapısının olmadığı lokasyonlarda ortam koşullarının takibi hayati önem taşır:

- **İnternetsiz ve Bağımsız Çalışma:** Sistem Wi-Fi ya da mobil veri paketine ihtiyaç duymaz; yalnızca standart 2G hücresel SMS şebekesini kullanır.
- **Hassas Ortam Ölçümü:** Deneyap Sıcaklık ve Nem Sensörü ortamın sıcaklığını (°C) ve bağıl nem oranını (%) I2C veriyoluyla milimetrik ölçer.
- **Otonom SMS Raporlama:** Ölçülen değerler belirlenen periyotlarla (`Sicaklik: 24.5C \n Nem: %45`) formatında hedef telefon numarasına SMS olarak fırlatılır.
- **Kararlı Batarya Güç Mimarisi:** GSM modülünün şebeke ararken ve SMS atarken çektiği 2A pik akımını karşılamak üzere sisteme **3.7V 2000mAh LiPo Batarya** entegre edilmiştir.

---

<a id="devre-ve-demo"></a>
## 📸 2. Devre Şeması ve Canlı SMS Gönderim Demosu

> 💡 **Görsel Sunum:** Fritzing breadboard devre şeması ve telefon ekranına gelen anlık SMS gönderim videosu aşağıda yan yana sunulmuştur:

<div align="center">
  <table>
    <tr>
      <td width="50%" align="center" valign="top">
        <b>🔌 Breadboard Devre Şeması</b><br/><br/>
        <!-- Yüklediğin devre şeması fotoğrafının linkini buraya yapıştır -->
<img width="592" height="237" alt="image" src="https://github.com/user-attachments/assets/e13f33fb-ee8c-46b8-9e70-e04a2e743b7d" />
        <br/><br/><em>Deneyap Kart 1A, I2C Sensör, SIM800C Modülü ve 3.7V LiPo Batarya</em>
      </td>
      <td width="50%" align="center" valign="top">
        <b>📲 Canlı SMS Gönderim Demosu (Video)</b><br/><br/>
        <!-- Çektiğin SMS videosunun linkini buraya yapıştır -->
        <video src="https://github.com/user-attachments/assets/151e5f51-6bfd-45f3-bb0f-d3bb083c9bd1" controls="controls" muted="muted" width="100%"></video>
        <br/><br/><em>Telefona Gerçek Zamanlı SMS Bildiriminin Ulaşma Anı</em>
      </td>
    </tr>
  </table>
</div>

---

<a id="donanimlar"></a>
## 🧰 3. Kullanılan Donanımlar ve Modüller

| Bileşen | Model / Açıklama | Görev |
| :--- | :--- | :--- |
| **Geliştirme Kartı** | Deneyap Kart 1A (ESP32) | Sensör verisini işleme ve SoftwareSerial ile SIM800C yönetimi |
| **GSM Modülü** | SIM800C GSM/GPRS Modülü | Hücresel şebekeye bağlanıp SMS gönderme |
| **Mesafe/Nem Sensörü**| Deneyap Sıcaklık ve Nem Ölçer | I2C üzerinden sıcaklık (°C) ve nem (%) ölçümü |
| **Güç Kaynağı** | 3.7V 2000mAh LiPo Batarya | SIM800C'nin anlık 2A akım ihtiyacını karşılama |
| **Anten** | Harici GSM Yay Anteni | Şebeke sinyal seviyesini güçlendirme |

---

<a id="pin-haritasi"></a>
## 🔌 4. Pin Haritası ve Bağlantı Tablosu

```text
+------------------------------------+              +-----------------------------+
|          Deneyap Kart 1A           |              |       Sensör / Modül        |
|                                    |              |                             |
|  D8 (SoftwareSerial RX)            |<------------>| SIM800C TX Pini             |
|  D14 (SoftwareSerial TX)           |------------->| SIM800C RX Pini             |
|  I2C SDA & SCL                     |<------------>| Sıcaklık ve Nem Sensörü     |
|  3.3V                              |------------->| Sensör VCC Beslemesi        |
|  Ortak GND                         |<------------>| Kart, Sensör & SIM800C GND  |
+------------------------------------+              +-----------------------------+
                                                    +-----------------------------+
                                                    |   3.7V 2000mAh LiPo Batarya |
                                                    |   Kırmızı (+) -> SIM800C VCC|
                                                    |   Siyah   (-) -> Ortak GND  |
                                                    +-----------------------------+
```

> 💡 **Önemli Donanım & Güç Notu:**
> - SIM800C çalışma gerilimi **3.4V – 4.4V** aralığındadır. Deneyap Kart'ın 3.3V pini yetersiz kalabilir veya kartı yeniden başlatabilir.
> - Bu nedenle şemada olduğu gibi **3.7V LiPo batarya doğrudan SIM800C VCC'sine** bağlanmalı ve tüm toprak hatları (**Ortak GND**) birleştirilmelidir.
> - Zayıf çeken kapalı alanlarda **anten** kullanımı sinyal bağlantısı için zorunludur.

---

<a id="sms-mantigi"></a>
## 📡 5. AT Komutları ile SMS İletişim Mantığı

Gömülü yazılım, SIM800C modülü ile standart **Hayes AT Komut Seti** üzerinden haberleşir:

1. **`AT`** ➔ Modülün hatta olup olmadığını kontrol eder (`OK` cevabı döner).
2. **`AT+CMGF=1`** ➔ Modülü **Metin (Text) SMS moduna** alır (PDU modu yerine okunabilir ASCII metin).
3. **`AT+CMGS="+905XXXXXXXXX"`** ➔ Hedef telefon numarasını belirler ve mesaj girişini başlatır (`>` karakteri beklenir).
4. **`mesaj`** ➔ Sıcaklık ve nem değerlerini içeren metin basılır.
5. **`mySerial.write(26)`** ➔ Klavyedeki **`CTRL+Z`** tuşuna karşılık gelen ASCII 26 baytı gönderilerek SMS hücresel şebekeye fırlatılır.

---

<a id="kurulum-ve-calistirma"></a>
## 🚀 6. Kurulum ve Çalıştırma Rehberi

### 1. SIM Kart Hazırlığı
- SIM kartınızı bir telefona takarak **PIN Kodu Sorgulamasını KAPATIN**.
- Kartın SMS gönderebilecek aktif bir hatta ve pakete sahip olduğunu teyit edin.

### 2. Kodu Özelleştirme
`sim800c_sicaklik_nem.ino` dosyasını açıp SMS alacak kendi telefon numaranızı girin:
```cpp
sendSMS("905XXXXXXXXX", mesaj); // 90 ile başlayan 12 haneli numara
```

### 3. Kodu Yükleme
- Arduino IDE'de **Deneyap Kart 1A** seçin.
- `Deneyap_SicaklikNemOlcer` ve `SoftwareSerial` kütüphanelerinin kurulu olduğundan emin olun.
- Kodu karta yükleyin. Sistem açıldıktan birkaç saniye sonra telefonunuza sıcaklık ve nem SMS'i gelecektir.

---

<a id="sorunlar-ve-cozumleri"></a>
## ⚠️ 7. Karşılaşılabilecek Sorunlar ve Çözümleri

### 1. SMS Gelmiyor / Modül Cevap Vermiyor
- **Neden:** RX ve TX pinleri ters bağlanmış olabilir ya da SIM kart PIN koduna takılı kalmıştır.
- **Çözüm:** Deneyap D8 pininin SIM800C TX'e, D14 pininin SIM800C RX'e gittiğinden emin olun.

### 2. Modül Işığı Hızlı Yanıp Sönüyor ve Kapanıyor
- **Neden:** Batarya gerilimi 3.4V altına düşmüş ya da akım yetersiz kalmıştır.
- **Çözüm:** LiPo bataryayı şarj edin ve ortak GND bağlantısını kontrol edin.

---

<a id="gelistirici"></a>
## 👩‍💻 8. Geliştirici

**Kevser ÜSTÜN**  
🎓 Giresun Üniversitesi — Bilgisayar Mühendisliği  
🔗 [GitHub Profilim](https://github.com/kvsrustun)

---

<a id="lisans"></a>
## 📄 9. Lisans

Bu proje [MIT Lisansı](LICENSE) kapsamında açık kaynak olarak paylaşılmıştır.



