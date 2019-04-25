<h1>Görüntü işleme kütüphanesi</h1>

	Hazırlayan: Orkhan ALIYEV

Yapılan işlemler sırası ile:<br>
<ol>
<li>Maske gezdirme</li>
<li>Büyütme işlemi (Zoom in)</li>
<li>Histogram çıkarma</li>
<li>Histogram eşitleme</li>
<li>Clustering(K-Means)</li>
<li>Morfoloji işlemleri</li>
<ul>
<li>Dilation</li>
<li>Erosion</li>
</ul>
<li>Nesne algılama</li>
<li>Görüntü Geometrisi</li>
<ul>
<li>Görüntüyü taşıma</li>
<li>Görüntüyü döndürme</li>
<li>Görüntüyü döndürme(Alias ile)</li>
<li>Görüntüyü aynalama</li>
</ul>
</ol>
<h2 align="center">Maske gezdirme</h2>
Gezdireceğimiz maskeyi görüntünün üzerine koyduğumuzda kenarlardan taşma olacak bu yüzden görüntünün kenarlarını sıfırlarla dolduruyoruz. Birinci iterasyonda maskenin merkezini görüntünün ilk pikseline koyuyoruz, görüntünün ilk pikselinin yeni değerini maskenin elemanlarını görüntüde üstünde durduğu piksellerle çarpıp topluyoruz ve görüntünün o pikselini bu toplam değeri ile setliyoruz. Devamında bir sağa kaydırıp aynı işlemi tekrarlıyoruz.
           <h2 align="center">Büyütme işlemi (Zoom in)</h2>
Görüntü üzerinde belirli bir kısmı kesip, çıkartıp onu büyütme işlemini gerçekleştirmek şu şekilde gerçekleşir. Örneğin fare ile fotoğrafın içerisinde herhangi bir noktadan başladık, sol alta doğru kırptık ve fareyi çektik. Başlangıç konumunu x0, y0 olarak bitiş konumunu x1, y1 olarak ele aldık bir döngü ile bu kısmı kesip çıkardık fakat yeni fotoğrafımız henüz büyütülmemiş. Büyütme için yeni fotoğrafın piksellerinin aralarını sıfırlar ile dolduruyoruz. Sonuçta yeni fotoğrafımız gürültülü gibi gözüküyor, bunun sebebi araları sıfırlar ile doldurmamız. Fotoğrafımız büyük fakat gürültülü bunu yok etmek için maske gezdiriyoruz. Gaussian maskesi ile maske gezdirme fonksiyonundaki adımları izlersek gürültüyü yok etmiş oluruz ve sonuca ulaşırız.
			        <h2 align="center">Histogram çıkarma</h2>
Fotoğrafta 0 ila 255 arasındaki piksel değerlerinin sayısını bir chart üzerinde gösterebilmek için bir döngü içerisinde fotoğrafın her pikseline erişiriz ve o piksel değerine sahip olan kaç tane piksel var ise bu sayıyı chart üzerinde setleriz.
				<h2 align="center">Histogram eşitleme</h2>
Çıkarmış olduğumuz histogram üzerinden histogram eşitleme yapmak için ilk olarak running sum hesaplanır, running sum’ın son değeri bizim toplam piksel değerimiz oluyor değerimiz oluyor. Her değeri bu toplam piksel değerimize böleceğiz. Daha sonra her değeri maksimum gri seviye değeri (örn. 255) ile çarpıyoruz. Ve elde ettiğimiz değerler bizim eşitlenmiş histogram değerlerimiz oluyor. Sonuçları eşitlenmiş histogram olarak chart üzerinde işliyoruz.
				<h2 align="center">Clustering(K-Means)</h2>
Görüntü üzerinde clustering işlemi yapmak için ilk olarak görüntünün histogramını çıkarmalıyız daha sonra bu histogram üzerine 2 eşik değerini(örn. T1 ve T2) rastgele setlemeliyiz. Daha sonra ise bir döngü içerisinde bu eşik değerlerinin yeni değerlerini bulabilmek için her eşik değeri için ona yakın olan pikseller ile değerlerini çarpıp toparız ve toplam piksel değerine böleriz. Bunu yaparken her iterasyonda bir önceki eşik değerleri ile yeni bulduğumuz eşik değerleri eşit mi diye kontrol ederiz ve sonuç sağlanana kadar iterasyon tekrarlanır. En sonda ise eşitlik sağlandığında o eşik değerlerinin komşularına karar veririz ve binary değerler ile görüntüyü binary görüntüye dönüştürürüz.
				  	<h2 align="center">Dilation</h2>
Dilation işlemini yaparken fotoğrafın binary halini kullanıyoruz. Görüntüdeki 1’ler üzerinden ilerliyoruz ve genişletme için OR’lama işlemi yapıyoruz. Bu işlem sonucunda genişletilmiş görüntüyü elde ederiz. 
					<h2 align="center">Erosion</h2>
Dilation işlemi gibi bu işlemi de binary görüntü üzerinde yaparız. Fakat tek fark OR’lama işlemi yerine AND’leme işlemi yapmamız. Bu işlem sonucunda eroziyona uğramış görüntüyü elde ederiz.
				<h2 align="center"> Nesne algılama</h2>
 
Görüntü üzerinde 4’lü veya 8’li şekilde geziyoruz, komşuların etiket değerlerini kontrol ediyoruz, eğer etiket almamışsa yeni etiket değerini veriyoruz veya komşularında etiket alan varsa onun değerine setliyoruz. Fakat komşularında 2 veya daha fazla etiket almış komşu olabilir bu duruma ”collision” diyoruz ve bu durumda çözüm olarak komşularını ve kendisini en küçük etiketli değere setliyoruz. Bu şekilde döngü sonuna kadar ilerliyoruz. Kaç etiketimiz var ise o kadar da nesne olduğu anlamına gelir. Ve bu etiket sayısını nesne sayısı olarak ekranda gösteririz.
			      <h2 align="center">Görüntüyü taşıma</h2>
Taşıma operatörü, giriş resmindeki her pikseli, çıkış resmindeki yeni bir konuma taşıma işlemidir. Orjinal resimdeki (x1,y1) koordinatındaki her piksel belli bir öteleme mesafesi (βx, βy) boyunca taşınarak yeni konumu olan (x2,y2) koordinatına yerleştirilir
 
Yukarıdaki formülden yaralanırız.
Yeni oluşan koordinatlar (x2,y2) resmin sınırları dışına çıktıysa ya yok sayılır veya sınırlar genişletilerek, ilgili alan doldurulur.  
         <h2 align="center"> Görüntüyü döndürme</h2>
Döndürme işlemi bir nokta etrafında belli bir açı (θ) değerinde çevirerek giriş resmindeki (x1,y1) koordinatını çıkış resmindeki (x2,y2) noktasına taşıma işlemidir. Döndürme işleminde sınırların dışına çıkan kısımlar yok sayıyoruz. 
 
Yukarıdaki formülden yararlanarak döndürme işlemini gerçekleştiririz. Gürültüsüz görüntü elde edemeyiz bunu elde etmek için alias ile döndürmeye ihtiyaç duyarız.
		       <h2 align="center">Görüntüyü döndürme(Alias ile)</h2>
Yukarıdaki işlemlerin aynısını uygularız fakat Alias’sız işlemde bazı piksellerden geçilmiyordu(vektör bazında baktığımızda) ve bu yüzden piksellerin değerleri belirsiz kalıyordu Alias ile döndürmede bu sorun çözülüyor. Piksellerden geçilmese de komşularının değerlerine yakın değerler alınırsa bu sorun çözülür.
Not: Bunu kaydırma işlemleri ile de yapabiliriz. Fakat iyi çözüm olmaz.
			                       <h2 align="center"> Aynalama</h2>
Görüntüyü  orijinal (x1, y1) konumundan alarak, belirlenen eksen etrafında yansıtarak yeni bir konuma (x2, y2)yerleştiririz. (x0,y0) noktası resmin tam orta noktasıdır.
•	x0 noktasından geçen dikey eksen etrafında yansıtma;
 
•	y0 noktasından geçen yatay eksen etrafında yansıtma,
    


•	(x0,y0) noktasından geçen herhangi bir θ açısına sahip bir eksen etrafında yansıtma.
 
 
