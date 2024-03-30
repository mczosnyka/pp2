#ifndef WINDOWS_H
#define WINDOWS_H

#include <string>
#include <vector>
#include <cstdint> // uint32_t
#include <utility> // std::pair

struct User;
using namespace std;
/**
Państwa zadaniem jest napisanie klasy Windows, która ma zawierać następujące składowe (typy do uzupełnienia):
1. `version_` - wersja, wartość domyślna, ustawiana w klasie, to `"11"`.
    1. Proszę do niej utworzyć metodę do odczytu `version()`.
2. `std::size_t activated_systems_` - jest to ilość aktywowanych Windowsów, wspólna dla wszystkich klas.
    W konstruktorze powinna być zwiększana.
    1. Proszę do niej utworzyć statyczną metodę do odczytu `activated_systems()`
3. `users_` - są to użytkownicy systemu, typ dowolny, polecam jednak `std::vector`.
    Struktura na użytkowników jest w pliku `user.h`
4. `character_type` - jest to przezwisko typu `wchar_t`

Oraz następujące metody (poza powyższymi getterami):
1. Konstruktor bezargumentowy, powinien on wypisywać: `"Windows " << version_ << '\n'`, oraz inkrementować `activated_systems_`
   - Jakbyśmy nie zdefiniowali konstruktora domyślnego to co by się stało?
2. Konstruktor przyjmujący wersję, powinien robić co powyższy jw.
   - O czym jeszcze powinienem paniętać aby `activated_systems_` faktycznie przy każdej konstrukcji się zwiększało?
3. Metodę `add_user` zwracającą id kolejnego użytkownika (czyli ilość elementów `users_` - 1), przyjmującą `user_name` i `password`.
   Nowy użytkownik powinien być dodany do `users_`.
4. Metodę `user`, która przyjmując `user_id` zwróci konkretnego użytkownika
5. Metodę `user_home_directory`, która przyjmując `user_id` zwróci ścieżkę do katalogu użytkownika, czyli `C:\Users\username`
6. *Zachęcam jeszcze do implementacji następujących metod:
   1. `static std::string default_text_file_encoding()` - domyślny system kodowania plików tekstowych
   2. `static std::string end_of_line()` - znak/znaki na końcu każdej linii
   3. `constexpr static bool is_path_case_sensitive()` - czy w ścieżkach wielkość znaków ma znaczenie
   4. `constexpr static char path_separator()` - jaki separator występuje w ścieżce do pliku lub katalogu
   5. `static std::string shortcut_to_send_end_of_file_to_program()` - jakim skrótem klawiszowym wysłać do programu EOF - end of file
   6. `static std::pair<std::string, std::string> user_login_information()` - ma to zwrócić ścieżki do plików: https://stackoverflow.com/a/5915362/1350091
      - co to są za pliki?
   7. `static std::string users_directory()` - ma zwrócić domyślną ścieżkę, gdzie tworzone są katalogi użytkowników
   - **Mają one pomóc w lepszym zrozumieniu istotnych, z punktu widzenia programowania, różnic między systemami.**
7. Jeśli zrobiłem gdzieś błąd proszę o zgłoszenie.
8. Po dokonaniu implementacji proszę zakomentować makro `UNIMPLEMENTED_WINDOWS_CLASS`
 **/

// #define UNIMPLEMENTED_WINDOWS_CLASS

class Windows
{
    string version_;
    static inline size_t activated_systems_ = 0;
    vector<User> users_;

public:
    Windows(): version_("11"){
        activated_systems_++;
        cout << "Windows " << version_ << '\n';
    }

    Windows(string version) {
        activated_systems_++;
        version_ = version;
        cout << "Windows " << version_ << '\n';
    }





    static size_t activated_systems();
    string version();
    using character_type = wchar_t;
    int add_user(string user_name_, string password_);
    User user(int &user_id);
    string user_home_directory(int &user_id);


};

#endif // WINDOWS_H
