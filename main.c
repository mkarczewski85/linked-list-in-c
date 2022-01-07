#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

/**
 * struktura dla pojedynczej instancji danych (rekordu)
 */
typedef struct DataRecord {
    int value; // pole wartości przechowywane w strukturze rekordu
} DataRecord_type;

/**
 * struktura pojedynczego elementu listy dwukierunkowej
 */
typedef struct Element {
    struct DataRecord *data;
    struct Element *prev;
    struct Element *next;
} Element_type;

/**
 * W tej sekcji wymieniamy funkcje implementujące mechanizm listy dwukierunkowej
 *
 */
void show_list(Element_type *head);

void show_reverse(Element_type *head);

int list_size(Element_type *head);

void push_front(Element_type **head, int value);

void push_back(Element_type **head, int value);

void push_by_index(Element_type **head, int value, int index);

void pop_front(Element_type **head);

void pop_back(Element_type **head);

void pop_by_index(Element_type **head, int index);

void show_by_index(Element_type **head, int index);


DataRecord_type *getNewRecord(int value);

/**
 * funkcja sterująca programem
 *
 */
int main() {
    Element_type *head; // zmienna wskaźnikowa wskazująca na czoło listy
    head = (Element_type *) malloc(sizeof(Element_type)); // alokujemy pamięć dla typu
    head = NULL; // na początku lista jest pusta, dlatego nie ma początku (ani końca)

    // inicjalizacja zmiennych wprowadzanych przez użytkownika
    int option = -1; // opcja wyboru
    int input_value = -1; // wartość do przechowania na liście
    int position = -1; // numer pozyycji elementu na liście (pozycja liczona od 1; index liczony od 0)

    system("cls"); // komenda systemowa dla wyczyszczenia terminala

    // powtarzaj do momentu zakończenia programu
    while (option != 0) {

        printf("\n\nOPCJE:\n\n");
        printf("1. Dodaj element na poczatek listy.\n");
        printf("2. Dodaj element na koniec listy.\n");
        printf("3. Dodaj element na wybrana pozycje listy.\n");
        printf("4. Usun element z poczatku listy.\n");
        printf("5. Usun element z konca listy.\n");
        printf("6. Usun element z wybranej pozycji.\n");
        printf("7. Wyswietl liste od poczatku.\n");
        printf("8. Wyswietl liste od konca.\n");
        printf("0. Wyjdz.\n\n");

        scanf("%i", &option); // czytaj wybór użytkownika

        // stale komunikatów w menu
        static const char VALUE_INPUT_PROMPT_MSG[] = "Wpisz wartosc do przechowania: ";
        static const char POSITION_INPUT_PROMPT_MSG[] = "Podaj nr pozycji na liscie: ";
        static const char WRONG_OPTION_ERROR_MSG[] = "Wybierz wlasciwa opcje (0-8).";

        switch (option) {
            case 0:
                return 0; // wyjdz
            case 1:
                printf(VALUE_INPUT_PROMPT_MSG);
                scanf("%i", &input_value);
                push_front(&head, input_value);
                break;
            case 2:
                printf(VALUE_INPUT_PROMPT_MSG);
                scanf("%i", &input_value);
                push_back(&head, input_value);
                break;
            case 3:
                printf(VALUE_INPUT_PROMPT_MSG);
                scanf("%i", &input_value);
                printf(POSITION_INPUT_PROMPT_MSG);
                scanf("%i", &position);
                push_by_index(&head, input_value, position-1); // index liczony od zera dlatego index = position - 1
                break;
            case 4:
                pop_front(&head);
                break;
            case 5:
                pop_back(&head);
                break;
            case 6:
                printf(POSITION_INPUT_PROMPT_MSG);
                scanf("%i", &position);
                pop_by_index(&head, position-1); // index liczony od zera dlatego index = position - 1
                break;
            case 7:
                show_list(head);
                Sleep(1000);
                break;
            case 8:
                show_reverse(head);
                Sleep(1000);
                break;
            default:
                printf(WRONG_OPTION_ERROR_MSG);
                Sleep(1000);
                break;
        }
    }
    return 0;
}

/**
 * stworz nowy rekord danych
 * @param value
 * @return
 */
DataRecord_type *getNewRecord(int value) {
    DataRecord_type *data; // deklaracja zmiennej wskaźnikowej dla typu DataRecord_type
    data = (DataRecord_type *) malloc(sizeof(DataRecord_type)); // alokacja pamięci dla adresu
    data->value = value; // przypisanie wartości do pola w strukturze
    return data;
}

/**
 * dodaj element na czoło listy (na początek)
 * @param head
 * @param value
 */
void push_front(Element_type **head, int value) {

    // stwórz nową instancje struktury rekordu
    DataRecord_type *data = getNewRecord(value);

    if (*head == NULL) { // jeśli lista jest pusta (brak ostatniego elementu)
        *head = (Element_type *) malloc(sizeof(Element_type)); // stwórz nowy element w miejsce czoła listy
        (*head)->prev = NULL; // który nie ma elementu go poprzedzającego
        (*head)->next = NULL; // ani po nim następującego
        (*head)->data = data; // dodaj dane
    } else { // jeśli lista nie jest pusta
        Element_type *current; // stwórz nowy element oznaczony jako aktualny
        current = (Element_type *) malloc(sizeof(Element_type));
        current->data = data; // (z danymi)
        current->prev = NULL; // który nie ma elementu poprzedzającego
        current->next = (*head); // ale następującym po nim elementem będzie obecne czoło listy
        (*head)->prev = current; // zaś dla obecnego czoła listy aktualny element będzie elementem go poprzedzającym
        *head = current; // dlatego ostatecznie aktualny element staje się nowym czołem listy
    }

}

/**
 * dodaj element na ogon listy (na koniec)
 * @param head
 * @param value
 */
void push_back(Element_type **head, int value) {

    DataRecord_type *data = getNewRecord(value);

    if (*head == NULL) { // jeśli lista jest pusta postępuj tak jak w poprzedniej funkcji
        *head = (Element_type *) malloc(sizeof(Element_type));
        (*head)->data = data;
        (*head)->prev = NULL;
        (*head)->next = NULL;
    } else { // jeśli nie jest pusta
        Element_type *current = *head; // posłuż się wskaźnikiem, który ustaw na czoło listy

        while (current->next != NULL) { // iteruj po liście dopóki nie dojdziesz do końca
            current = current->next; // czyli do momentu, kiedy element nie będzie miał następnika
        }

        // znajdujesz się na ogonie listy (jej końcu); chcemy dodać od tej strony listy nowy element (ustalić nowy ogon)
        current->next = (Element_type *) malloc(sizeof(Element_type)); // aktualny ogon zyskuje następujący po nim element
        current->next->data = data; // (z danymi)
        current->next->prev = current; // aktualny ogon (current) staje się poprzednikiem nowo dodawanego elementu
        current->next->next = NULL; // zaś nowo dodany element nie ma elementu po nim następującego (staje się ogonem listy)
    }
}

/**
 * dodaj element na wyznaczone miejsce (pozycję) listy (index)
 * @param head
 * @param value
 * @param index
 */
void push_by_index(Element_type **head, int value, int index) {

    DataRecord_type *data = getNewRecord(value);

    if (index == 0) push_front(head, value); // jeśli index wynosi 0 to wstawiamy element na poczatku (od czoła)
    else {
        if (index == list_size(*head)) push_back(head, value); // jeśli index wskazuje na ostatni element, dodaj na koniec (od ogona)
        else { // w przeciwnym wypadku
            Element_type *current = *head; // posłuż się wskaźnikiem, który ustaw na czoło listy
            Element_type *tmp; // posłuż się zmienna wskaźnikową pomocniczą (tymczasową)

            int i = 0; // ustaw iterator na 0
            // dopóki jest kolejny element na liście a iterator jest mniejszy niż (index-1)
            while (current->next != NULL && i < index - 1) {
                current = current->next; // ustawiaj wskaźnik na kolejny element z listy
                i++; // inkrementuj iterator
            }

            // dochodzimy wskaźnikiem na element poprzedzający element na poszukiwanej pozycji (current)
            tmp = current->next; // ustaw zmienną pomocniczą na kolejny element (ten do podmiany) żeby go nie stracić podczas podmiany
            current->next = (Element_type *) malloc(sizeof(Element_type)); // alokujemy (podmieniamy) nowy (świeży) element na pozycji do podmiany
            current->next->data = data; // (dodajemy dane)
            current->next->prev = current; // ustawiamy na dodawanym elemencie (next) wskaźnik elementu poprzedzającego (prev) na element current
            tmp->prev = current->next; // element podmieniony (przesunięty) zyskuje nowy element poprzedzający w postaci dodawanego elementu
            current->next->next = tmp; // zaś u nowo dodanego elementu, ustawiamy przesunięty element jako element następny
            // nowy element wskoczył na miejsce w pozycji index, a stary element z tej pozycji przesunął się do tyłu listy
            // przykład: element na pozycji 5, zostaje przesunięty na pozycję 6, na pozycji 5 jest dodawany element
            // dla elementu na pozycji 4, następnym elementem jest nowy element (5), zaś dla elementu na pozycji 6
            // nowy element jest teraz elementem go poprzedzającym
        }
    }


}

/**
 * usuń (wyjmij) czoło listy (pierwszy element)
 * @param head
 */
void pop_front(Element_type **head) {

    if (*head != NULL) { // jeśli lista nie jest pusta
        if ((*head)->next == NULL) { // jeśli lista ma tylko 1 element
            *head = NULL; // usuń element
        } else { // jeśli lista ma więcej niż 1 element
            Element_type *tmp; // posłuż się zmienną pomocniczą
            tmp = (*head)->next; // ustaw go na następny element od czoła
            free(*head); // zwolnij pamięć po danych z czoła
            *head = tmp; // ustaw nowe czoło na element ze zmiennej pomocniczej
            (*head)->prev = NULL; // nowe czoło nie może mieć elementu poprzedzającego
        }
    }
}

/**
 * usuń (wyjmij) ogon listy (ostatni element)
 * @param head
 */
void pop_back(Element_type **head) {

    if ((*head)->next == NULL) {
        *head = NULL;
    } else {
        Element_type *current = *head; // zacznij od czoła
        while (current->next->next != NULL) { // iteruj do przedostatniego elementu
            current = current->next;
        }
        free(current->next); // wykasuj ostatni element
        current->next = NULL; // przedostatni element staje się ostatnim (nie ma następnego po nim)
    }
}

/**
 * usuń (wyjmij) element na wskazanej pozycji (index)
 */
void pop_by_index(Element_type **head, int index) {
    if (index == 0) pop_front(head); // jeśli index = 0, usuń pierwszy element (czoło listy)
    else {
        Element_type *current = *head;
        Element_type *tmp;

        int i = 0;
        while (current->next != NULL && i < index - 1) { // iteruj do pozycji poprzedzającej element do usunięcia
            current = current->next;
            i++;
        }

        // wyjęcie ze struktury usuwanego elementu
        tmp = current->next;
        current->next = tmp->next;
        current->next->prev = current;
        free(tmp); // i wykasowanie go z pamięci
    }


}

/**
 * wyświetl wartości przechowywane w liście (od czoła, początku)
 * @param head
 */
void show_list(Element_type *head) {
    printf("\n");
    if (head == NULL) printf("Lista jest pusta"); // jeśli nie ma czoła, to nie ma listy
    else {
        Element_type *current = head; // zacznij od czoła
        int i = 1; // licznik pozycji do wyświetlenia
        do {
            printf("%i : ", i);
            printf("%i", current->data->value);
            printf("\n");
            current = current->next; // przechodź do następnego elementu listy
            i++;
        } while (current != NULL); // do momentu jej końca
    }
}

/**
 * wyświetl wartości przechowywane w liście (od ogona, tyłu)
 * @param head
 */
void show_reverse(Element_type *head) {
    printf("\n");
    if (head == NULL) printf("Lista jest pusta");
    else {
        Element_type *current = head; // zacznij od czoła
        while (current->next != NULL) { // dojdź do końca listy
            current = current->next;
        }
        int i = list_size(head); // ustal liczbę wszystkich elementów listy
        do {
            printf("%i : ", i); // wyświetl numer pozycji
            printf("%i", current->data->value); // wyświetl przechowywaną wartość
            printf("\n");
            current = current->prev; // przejdź do poprzedniego elementu
            i--; // dekrementuj licznik pozycji w liście
        } while (current != NULL);
    }
}

/**
 * wyświetl element o wskazanym idexie
 * @param head
 * @param index
 */
void show_by_index(Element_type **head, int index) {

}

/**
 * funkcja zliczająca liczbę elementów listy (jej długość)
 * @param head
 * @return
 */
int list_size(Element_type *head) {
    int counter = 0; // inicjalizujemy licznik
    if (head == NULL) return counter; // jeśli lista jest pusta wzróć zero
    else { // jeśli nie jest pusta
        Element_type *current = head; // posłuż się wskźnikiem
        do {
            counter++; // inkrementuj licznik
            current = current->next; // ustawiaj wskaźnik na kolejny element z listy
        } while (current != NULL); // do momentu, aż skończą się elementy
    }
    return counter;
}