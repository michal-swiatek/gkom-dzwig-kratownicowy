# dżwig kratownicowy
# 2020

Projekt zrealizowany w ramach przedmiotu grafika komputerowa.
Celem projektu było przedstawienie dźwigu na placu budowy.

Zaimplementowana funkcjonalność:
*  Generowanie prostych brył (sześcian, cylinder, stożek)
*  Łączenie prostych brył w obiekty złożone
*  Animowanie obrotu dźwigu, liny oraz przesuwania pozycji haku dźwigu
*  Teksturowanie obiektów (generowanie współrzędnych uv)
*  Cieniowanie Phonga
*  Cienie kierunkowe
*  Skybox
*  Interaktywna kamera (pozwla na poruszanie się po świecie, zoom)
*  Możliwość nakłądania materiału za pomocą tekstur (ambient, diffuse, specular)

W celu uruchomieniu projektu nalezy pobrać pliki źródłowe oraz skrypty budujące 
z mastera. Następnie za pomocą CMake stworzyć projekt dla środowiska Visual Studio
(nalezy znawigować Cmake do CmakeLists.txt na poziomie gównego foderu, zawiera
on plik main.cpp)

Aby aplikacja została prawidłowo uruchomiona konieczne jest dostarczenie do niej
pliku glew32.dll, można go pobrać z oficjalnej strony: http://glew.sourceforge.net/
(nalezy użyć binariów 32 bitowych)
Plik powinien znajdowac się w tym samym folderze co plik wykonywalny
