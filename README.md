# RSA
Small scale RSA encryption. (PL/EN)

Protokół RSA to nowoczesny sposób przekazywania informacji z jawnym kluczem.  
W moim programie komunikacja zachodzi między ALICE która ustal klucz i jest odbiorcą wiadomości, a BOBem, który wysyła wiadomość.

Ideą działania RSA jest to, że Alice wysyła "w świat" swoje klucze,  
za pomocą których teoretycznie każdy może zakodować wiadomość,  
oraz wysłać jej tak, że tylko ona będzie mogła ją odkodować.  
Jest to możliwe dzięki paru matamatycznym sztuczkom, skupionym wokół
funkaji Eulera, jej właściwości, arytmetyki modularnej i liczb pierwszych.  
