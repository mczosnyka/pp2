#ifndef LINUX_H
#define LINUX_H

#include <string>
#include <vector>
#include <optional> // std::optional
#include <cstdint> // uint32_t
#include <utility> // std::pair
using namespace std;
struct User;  // declaration instead of include

/**
Państwa zadaniem jest napisanie klasy Linux, która ma zawierać następujące składowe (typy do uzupełnienia):
1. `distribution_` - nie istnieje system Linux, systemami są jego dystrybucje.
    Jak nie wiadomo jaka dystrybucja to `Ubuntu`, więc wartość domyślna, ustawiana w klasie, to `"Ubuntu"`.
    1. Proszę do niej utworzyć metodę do odczytu `distribution()`.
2. `std::size_t open_source_sympathizers_` - jest to ilość użytkowników Linuxa, wspólna dla wszystkich klas.
    W konstruktorze powinna być zwiększana, w destruktorze zmniejszana.
    1. Proszę do niej utworzyć statyczną metodę do odczytu `open_source_sympathizers()`
3. `users_` - są to użytkownicy systemu, typ dowolny, polecam jednak `std::vector`.
    Struktura na użytkowników jest w pliku `user.h`
4. `character_type` - jest to przezwisko typu `char`

Oraz następujące metody (poza powyższymi getterami):
1. Konstruktor bezargumentowy, powinien on wypisywać: `"+" << distribution_ << '\n'`, oraz inkrementować `open_source_sympathizers_`
   - Jakbyśmy nie zdefiniowali konstruktora domyślnego to co by się stało?
2. Konstruktor przyjmujący dystrybucje, powinien robić co powyższy jw.
   - O czym jeszcze powinienem paniętać aby `open_source_sympathizers_` faktycznie przy każdej konstrukcji się zwiększało?
3. Destruktor, który będzie dekrementował `open_source_sympathizers_`, oraz wyświetlał `"~" << distribution_ << '\n'`
   - jakbyśmy nie zdefiniowali destruktora to co by się stało?
4. Metodę `add_user` zwracającą id kolejnego użytkownika (czyli ilość elementów `users_` - 1), przyjmującą `user_name` i `password`.
   Nowy użytkownik powinien być dodany do `users_`.
5. Metodę `user`, która przyjmując `user_id` zwróci konkretnego użytkownika
6. Metodę `user_home_directory`, która przyjmując `user_id` zwróci ścieżkę do katalogu użytkownika, czyli `/home/username/`
7. Środowisko graficzne dla dystrybucji, nie każdy ją ma. Dlatego proszę o dodanie:
   1. Dodanie pola w klasie: `std::optional<std::string> graphic_environment_;`
   2. Dodanie metod dostępowych: `graphic_environment() const` i `set_graphic_environment`
8. *Zachęcam jeszcze do implementacji następujących metod:
   1. `static std::string default_text_file_encoding()` - domyślny system kodowania plików tekstowych
   2. `static std::string end_of_line()` - znak/znaki na końcu każdej linii
   3. `constexpr static bool is_path_case_sensitive()` - czy w ścieżkach wielkość znaków ma znaczenie
   4. `constexpr static char path_separator()` - jaki separator występuje w ścieżce do pliku lub katalogu
   5. `static std::string shortcut_to_send_end_of_file_to_program()` - jakim skrótem klawiszowym wysłać do programu EOF - end of file
   6. `static std::pair<std::string, std::string> user_login_information()` - ma to zwrócić ścieżki do plików `/etc/passwd` i `/etc/shadow`
      - co to są za pliki?
   7. `static std::string users_directory()` - ma zwrócić domyślną ścieżkę, gdzie tworzone są katalogi użytkowników
   - **Mają one pomóc w lepszym zrozumieniu istotnych, z punktu widzenia programowania, różnic między systemami.**
9. Jeśli zrobiłem gdzieś błąd proszę o zgłoszenie. Pierwsza osoba z roku, która zgłosi dany błąd ma plusa!
**/

class Linux
{
    // TODO:
    string distribution_;
    static inline size_t open_source_sympathizers_ = 0;
    vector<User> users_;

public:
    Linux(): distribution_("Ubuntu"){
        open_source_sympathizers_++;
        cout << "+" << distribution_ << '\n';
    }

    Linux(string distribution) {
        open_source_sympathizers_++;
        distribution_ = distribution;
        cout << "+" << distribution_ << '\n';
    }

    ~Linux(){
        open_source_sympathizers_--;
        cout << "~" << distribution_ << '\n';
    }

    std::optional<std::string> graphic_environment_;
    using character_type = char;
    string distribution();
    static size_t open_source_sympathizers();
    int add_user(string user_name_, string password_);
    User user(int &user_id);
    string user_home_directory(int &user_id);
    std::optional<std::string> graphic_environment() const;
    void set_graphic_environment(string graphic_environment);
};

#endif // LINUX_H
