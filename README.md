
Yapilan islemler sirasi ile:
1.	Maske gezdirme
2.	Büyütme islemi (Zoom in)
3.	Histogram çikarma
4.	Histogram esitleme
5.	Clustering(K-Means)
6.	Morfoloji islemleri
a.	Dilation
b.	Erosion
7.	Nesne algilama
8.	Görüntü Geometrisi
a.	Görüntüyü tasima
b.	Görüntüyü döndürme
c.	Görüntüyü döndürme(Alias ile)
d.	Görüntüyü aynalama

Maske gezdirme
Gezdirecegimiz maskeyi görüntünün üzerine koydugumuzda kenarlardan tasma olacak bu yüzden görüntünün kenarlarini sifirlarla dolduruyoruz. Birinci iterasyonda maskenin merkezini görüntünün ilk pikseline koyuyoruz, görüntünün ilk pikselinin yeni degerini maskenin elemanlarini görüntüde üstünde durdugu piksellerle çarpip topluyoruz ve görüntünün o pikselini bu toplam degeri ile setliyoruz. Devaminda bir saga kaydirip ayni islemi tekrarliyoruz.
           Büyütme islemi (Zoom in)
Görüntü üzerinde belirli bir kismi kesip, çikartip onu büyütme islemini gerçeklestirmek su sekilde gerçeklesir. Örnegin fare ile fotografin içerisinde herhangi bir noktadan basladik, sol alta dogru kirptik ve fareyi çektik. Baslangiç konumunu x0, y0 olarak bitis konumunu x1, y1 olarak ele aldik bir döngü ile bu kismi kesip çikardik fakat yeni fotografimiz henüz büyütülmemis. Büyütme için yeni fotografin piksellerinin aralarini sifirlar ile dolduruyoruz. Sonuçta yeni fotografimiz gürültülü gibi gözüküyor, bunun sebebi aralari sifirlar ile doldurmamiz. Fotografimiz büyük fakat gürültülü bunu yok etmek için maske gezdiriyoruz. Gaussian maskesi ile maske gezdirme fonksiyonundaki adimlari izlersek gürültüyü yok etmis oluruz ve sonuca ulasiriz.
			        Histogram çikarma
Fotografta 0 ila 255 arasindaki piksel degerlerinin sayisini bir chart üzerinde gösterebilmek için bir döngü içerisinde fotografin her pikseline erisiriz ve o piksel degerine sahip olan kaç tane piksel var ise bu sayiyi chart üzerinde setleriz.
				Histogram esitleme
Çikarmis oldugumuz histogram üzerinden histogram esitleme yapmak için ilk olarak running sum hesaplanir, running sum’in son degeri bizim toplam piksel degerimiz oluyor degerimiz oluyor. Her degeri bu toplam piksel degerimize bölecegiz. Daha sonra her degeri maksimum gri seviye degeri (örn. 255) ile çarpiyoruz. Ve elde ettigimiz degerler bizim esitlenmis histogram degerlerimiz oluyor. Sonuçlari esitlenmis histogram olarak chart üzerinde isliyoruz.

				Clustering(K-Means)
Görüntü üzerinde clustering islemi yapmak için ilk olarak görüntünün histogramini çikarmaliyiz daha sonra bu histogram üzerine 2 esik degerini(örn. T1 ve T2) rastgele setlemeliyiz. Daha sonra ise bir döngü içerisinde bu esik degerlerinin yeni degerlerini bulabilmek için her esik degeri için ona yakin olan pikseller ile degerlerini çarpip topariz ve toplam piksel degerine böleriz. Bunu yaparken her iterasyonda bir önceki esik degerleri ile yeni buldugumuz esik degerleri esit mi diye kontrol ederiz ve sonuç saglanana kadar iterasyon tekrarlanir. En sonda ise esitlik saglandiginda o esik degerlerinin komsularina karar veririz ve binary degerler ile görüntüyü binary görüntüye dönüstürürüz.
				  	Dilation
Dilation islemini yaparken fotografin binary halini kullaniyoruz. Görüntüdeki 1’ler üzerinden ilerliyoruz ve genisletme için OR’lama islemi yapiyoruz. Bu islem sonucunda genisletilmis görüntüyü elde ederiz. 
					Erosion
Dilation islemi gibi bu islemi de binary görüntü üzerinde yapariz. Fakat tek fark OR’lama islemi yerine AND’leme islemi yapmamiz. Bu islem sonucunda eroziyona ugramis görüntüyü elde ederiz.
				 Nesne algilama
 
Görüntü üzerinde 4’lü veya 8’li sekilde geziyoruz, komsularin etiket degerlerini kontrol ediyoruz, eger etiket almamissa yeni etiket degerini veriyoruz veya komsularinda etiket alan varsa onun degerine setliyoruz. Fakat komsularinda 2 veya daha fazla etiket almis komsu olabilir bu duruma ”collision” diyoruz ve bu durumda çözüm olarak komsularini ve kendisini en küçük etiketli degere setliyoruz. Bu sekilde döngü sonuna kadar ilerliyoruz. Kaç etiketimiz var ise o kadar da nesne oldugu anlamina gelir. Ve bu etiket sayisini nesne sayisi olarak ekranda gösteririz.
			      Görüntüyü tasima
Tasima operatörü, giris resmindeki her pikseli, çikis resmindeki yeni bir konuma tasima islemidir. Orjinal resimdeki (x1,y1) koordinatindaki her piksel belli bir öteleme mesafesi (ßx, ßy) boyunca tasinarak yeni konumu olan (x2,y2) koordinatina yerlestirilir
 
Yukaridaki formülden yaralaniriz.
Yeni olusan koordinatlar (x2,y2) resmin sinirlari disina çiktiysa ya yok sayilir veya sinirlar genisletilerek, ilgili alan doldurulur.  
          Görüntüyü döndürme
Döndürme islemi bir nokta etrafinda belli bir açi (?) degerinde çevirerek giris resmindeki (x1,y1) koordinatini çikis resmindeki (x2,y2) noktasina tasima islemidir. Döndürme isleminde sinirlarin disina çikan kisimlar yok sayiyoruz. 
 
Yukaridaki formülden yararlanarak döndürme islemini gerçeklestiririz. Gürültüsüz görüntü elde edemeyiz bunu elde etmek için alias ile döndürmeye ihtiyaç duyariz.
		       Görüntüyü döndürme(Alias ile)
Yukaridaki islemlerin aynisini uygulariz fakat Alias’siz islemde bazi piksellerden geçilmiyordu(vektör bazinda baktigimizda) ve bu yüzden piksellerin degerleri belirsiz kaliyordu Alias ile döndürmede bu sorun çözülüyor. Piksellerden geçilmese de komsularinin degerlerine yakin degerler alinirsa bu sorun çözülür.
Not: Bunu kaydirma islemleri ile de yapabiliriz. Fakat iyi çözüm olmaz.
			                        Aynalama
Görüntüyü  orijinal (x1, y1) konumundan alarak, belirlenen eksen etrafinda yansitarak yeni bir konuma (x2, y2)yerlestiririz. (x0,y0) noktasi resmin tam orta noktasidir.
•	x0 noktasindan geçen dikey eksen etrafinda yansitma;
 
•	y0 noktasindan geçen yatay eksen etrafinda yansitma,
    


•	(x0,y0) noktasindan geçen herhangi bir ? açisina sahip bir eksen etrafinda yansitma.
 
 
