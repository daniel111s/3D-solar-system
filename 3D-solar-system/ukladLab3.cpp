//////////////////////////////////////////////////////////////////////////////////////////
// Program demonstruje  skladanie transformacji przy modelowaniu zlozonych obiektow
// skladajacych sie z wielu elementow ruchomych (ramie robota). 

#include <GL/glut.h>
#include<stdio.h>
#include <iostream>
#include <chrono>
#include <cmath>

// Stale wyznaczajace predkosci katowe planety i ksiezyca (w stopniach/klat.)
#define PREDKOSC_KATOWA_PLANETY  -0.25   //CW
#define PREDKOSC_KATOWA_KSIEZYCA 0.5   //CCW
//#define PREDKOSC_ORBITA_PLANETA -12.0    //CW
//#define PREDKOSC_ORBITA_KSIEZYCA 16.0    //CCW

// Wskazniki do wykorzystywanych kwadryk
GLUquadricObj* podstawaSciany;
GLUquadricObj* podstawaDyskG;
GLUquadricObj* przegubSciany;
GLUquadricObj* przegubDyskG;
GLUquadricObj* przegubDyskD;
GLUquadricObj* glowicaSciany;
GLUquadricObj* glowicaDyskG;
GLUquadricObj* glowicaDyskD;
GLUquadricObj* orbitaPlaneta1;
GLUquadricObj* orbitaKsiezyc1;
GLUquadricObj* orbitaPlaneta2;
GLUquadricObj* orbitaPlaneta3;

GLfloat rotObsY = 40.0;
GLfloat rotObsX = 40.0;
//1_b 
GLfloat rotObsZ = 0.0;

GLfloat rotPodstawy = 0.0;
GLfloat rotRamienia1 = 40.0;
GLfloat rotRamienia2 = -40.0;
GLfloat rotGlowicy = 20.0;
GLfloat rozUchwytow = 0.5;

//1a Odleglosc obserwatora od obiektu - zakres <3;350> poczatkowo 70
GLfloat odl_obs_od_obiektu = 70.0;
GLfloat odl_min = 3.0;
GLfloat odl_max = 350.0;

GLfloat katPlaneta = 0.0;
GLfloat katOrbitaPlaneta = 0.0;
GLfloat katKsiezyc = 0.0;
GLfloat katOrbitaKsiezyc = 0.0;
GLfloat katPlaneta2 = 0.0;
GLfloat katOrbitaPlaneta2 = 0.0;
GLfloat katPlaneta3 = 0.0;
GLfloat katOrbitaPlaneta3 = 0.0;

GLfloat alfa = 1.0;

const std::chrono::time_point<std::chrono::high_resolution_clock> start =
std::chrono::high_resolution_clock::now();


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja inicjujaca elementy skladowe ramienia robota zamodelowane jako kwadryki
// 
void InicjujRamieRobota(void)
{
    // Zainicjowanie scian bocznych walca bedacego podstawa ramienia
    podstawaSciany = gluNewQuadric();
    gluQuadricDrawStyle(podstawaSciany, GLU_LINE);

    // Zainicjowanie gornej podstawy walca 
    podstawaDyskG = gluNewQuadric();
    gluQuadricDrawStyle(podstawaDyskG, GLU_LINE);

    // Zainicjowanie scian bocznych cylindrycznego przegubu ramienia
    przegubSciany = gluNewQuadric();
    gluQuadricDrawStyle(przegubSciany, GLU_LINE);

    // Zainicjowanie gornej podstawy walca 
    przegubDyskG = gluNewQuadric();
    gluQuadricDrawStyle(przegubDyskG, GLU_LINE);

    // Zainicjowanie dolnej podstawy walca 
    przegubDyskD = gluNewQuadric();
    gluQuadricDrawStyle(przegubDyskD, GLU_LINE);

    // Zainicjowanie scian bocznych cylindra glowicy 
    glowicaSciany = gluNewQuadric();
    gluQuadricDrawStyle(glowicaSciany, GLU_LINE);

    // Zainicjowanie gornej podstawy walca 
    glowicaDyskG = gluNewQuadric();
    gluQuadricDrawStyle(glowicaDyskG, GLU_LINE);

    // Zainicjowanie dolnej podstawy walca 
    glowicaDyskD = gluNewQuadric();
    gluQuadricDrawStyle(glowicaDyskD, GLU_LINE);

}


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja rysujaca obraz sceny widzianej z biezacej pozycji obserwatora
// Zalozenie: Funkcja glutWireSpehere moze ryswac tylko sfere o promieniu 1  
void RysujRamieRobota(GLfloat obrotPodstawy, GLfloat obrotRamienia1,
    GLfloat obrotRamienia2, GLfloat obrotGlowicy,
    GLfloat rozstawUchwytow)
{
    // Pocztaek tworzenia ukladu wspolrzednych
    glBegin(GL_LINES);

    // Os X
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-200.0, 0.0, 0.0); //dlugosc osi
    glVertex3f(200.0, 0.0, 0.0);

    // Os Y
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -200.0, 0.0);
    glVertex3f(0.0, 200.0, 0.0);

    // Os Z
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -200.0);
    glVertex3f(0.0, 0.0, 200.0);

    // Koniec tworzenia ukladu wspolrzednych
    glEnd();

    //zmiany
    glPushMatrix();
    //
    glPopMatrix();


    glColor3f(1.0, 1.0, 1.0);




    // Przygotowanie stosu macierzy modelowania
    glPushMatrix();
    glTranslatef(-100.0, 0.0, -100.0);
    // Rysowanie podstawy ramienia (cylinder bez dolnej podstawy)
    glPushMatrix();
    // - sciany boczne
    glRotatef(-90.0, 1, 0, 0);
    gluCylinder(podstawaSciany, 3.0, 3.0, 1.0, 20, 4);

    // - gorna podstawa
    glTranslatef(0.0, 0.0, 1.0);
    gluDisk(podstawaDyskG, 0.0, 3.0, 20, 4);
    glPopMatrix();


    // Rysowanie dwoch wspornikow ramienia (prostopadlosciany)
    glPushMatrix();
    glScalef(3.0, 4.0, 1.0);
    glTranslatef(0.0, 3.0 / 4.0, 1.0);
    glutWireCube(1);
    glTranslatef(0.0, 0.0, -2.0);
    glutWireCube(1);
    glPopMatrix();

    // Wyznaczenie osi obrotu ramienia w plaszczyznie pionowej
    glTranslatef(0.0, 4.0, 0.0);

    // Obrot ramienia w plaszczyznie pionowej
    glRotatef(obrotRamienia1, 0, 0, 1);

    // Modelowanie ramienia nr 1
    glPushMatrix();
    glScalef(8.0, 1.0, 1.0);
    glTranslatef(3.5 / 8.0, 0.0, 0.0);
    glutWireCube(1);
    glPopMatrix();

    // Wyznaczenie osi obrotu ramienia 2 w plaszczyznie pionowej
    glTranslatef(7.5, 0.0, 0.0);

    // Obrot ramienia 2 wzgledem ramienia 1
    glRotatef(obrotRamienia2, 0, 0, 1);

    // Modelowanie przegubu (walca z obiema podstawami)
    glPushMatrix();
    // - sciany boczne
    glTranslatef(0.0, 0.0, -0.5);
    gluCylinder(podstawaSciany, 1.0, 1.0, 1.0, 20, 4);

    // - gorna podstawa
    gluDisk(podstawaDyskG, 0.0, 1.0, 20, 4);

    // - dolna podstawa
    glTranslatef(0.0, 0.0, 1.0);
    gluDisk(podstawaDyskG, 0.0, 1.0, 20, 4);
    glPopMatrix();

    // Modelowanie ramienia nr 2
    glPushMatrix();
    glScalef(4.0, 1.0, 1.0);
    glTranslatef(2.0 / 4.0, 0.0, 0.0);
    glutWireCube(1);
    glPopMatrix();

    // Wyznaczenie osi obrotu glowicy
    glTranslatef(4.0, 0.0, 0.0);
    glRotatef(90, 0, 1, 0);
    glRotatef(obrotGlowicy, 0, 0, 1);

    // Modelowanie glowicy (walca z oboma podstawami)
    glPushMatrix();
    // - sciany boczne
    gluCylinder(podstawaSciany, 1.0, 1.0, 1.0, 20, 4);

    // - gorna podstawa
    gluDisk(podstawaDyskG, 0.0, 1.0, 20, 4);

    // - dolna podstawa
    glTranslatef(0.0, 0.0, 1.0);
    gluDisk(podstawaDyskG, 0.0, 1.0, 20, 4);
    glPopMatrix();

    // Modelowanie uchwytu (dwoch prostopadloscianow, ktore sie rozsuwaja i zsuwaja)
    glTranslatef(0.0, 0.0, 1.5);
    glScalef(0.5, 0.5, 2.0);
    glTranslatef(-rozstawUchwytow, 0.0, 0.25);
    glutWireCube(1);
    glTranslatef(rozstawUchwytow * 2.0, 0.0, 0.0);
    glutWireCube(1);



    // Posprzatanie na stosie macierzy modelowania
    glPopMatrix();
}


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja generujaca pojedyncza klatke animacji
void WyswietlObraz(void)
{
    // Wyczyszczenie bufora ramki i bufora glebokosci
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Powielenie macierzy na wierzcholku stosu 
    glPushMatrix();

    // Wyznaczenie polozenia obserwatora (przeksztalcenie uladu wspolrzednych 
    // sceny do ukladu wspolrzednych obserwatora). 
    glTranslatef(0, 0, -odl_obs_od_obiektu);
    glRotatef(rotObsX, 1, 0, 0);
    glRotatef(rotObsY, 0, 1, 0);
    //1_b
    glRotatef(rotObsZ, 0, 0, 1);

    glPushMatrix();
    // Generacja obrazu sceny w niewidocznym buforze ramki
        //zad2
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RysujRamieRobota(rotPodstawy, rotRamienia1, rotRamienia2, rotGlowicy, rozUchwytow);
    glPopMatrix();

    //rysunek wiezy z zad 1 (zad2)
    glPushMatrix();
        glTranslatef(100.0, 0.0, -100.0); //przesuwam wieze

        //podstawa wiezy
        glPushMatrix();
            glColor3f(0.75, 0.0, 0.0);
            glTranslatef(0.0, 5.0, 0.0);
            glRotatef(45.0, 0, 1, 0);
            glScalef(4.23, 10.0, 4.23);
            glutSolidCube(1);
        glPopMatrix();

       
        //nadbudowka
        glPushMatrix();
            glColor3f(0.0, 0.75, 0.0);
            glTranslatef(0.0, 11.5, 0.0);
            glScalef(8.0, 3.0, 8.0);
            glutSolidCube(1);
        glPopMatrix();

       ///szescianki
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.75);

            glScalef(2.0, 2.0, 2.0);    
            glTranslatef(1.5, 7.0, -1.5);   //1
            glutSolidCube(1);
            
            glTranslatef(-3.0, 0.0, 0.0);   //2
            glutSolidCube(1);

            glTranslatef(0.0, 0.0, 3.0);   //3
            glutSolidCube(1);

            glTranslatef(3.0, 0.0, 0.0);   //4
            glutSolidCube(1);
            
        glPopMatrix();
        
    glPopMatrix();
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //animacja planet
    glPushMatrix();


        //slonce
        glPushMatrix();
            glColor3f(1.0, 1.0, 0.0);
            glRotatef(90.0, 1, 0, 0);   //pionowa os
            glutWireSphere(5.0, 20, 10);    //promien slonca 5.0
            //zainicjowanie dysku - orbity planety1 o promieniu 20
            orbitaPlaneta1 = gluNewQuadric();
            gluQuadricDrawStyle(orbitaPlaneta1, GLU_LINE);
            gluDisk(orbitaPlaneta1, 20.0, 20.0, 30, 20);    //rysowanie orbity planety 1

            //zainicjowanie dysku - orbity planeta2 o promieniu 60
            orbitaPlaneta2 = gluNewQuadric();
            gluQuadricDrawStyle(orbitaPlaneta2, GLU_LINE);
            glRotatef(45.0, 1, 0, 0);
            glColor3f(1.0, 0.0, 0.0);
            gluDisk(orbitaPlaneta2, 60.0,60.0, 20, 20);  //rysowanie orbity
            glRotatef(-45.0, 1, 0, 0);

            //zainicjowanie dysku - orbity planeta3 o promieniu 40
            orbitaPlaneta3 = gluNewQuadric();
            gluQuadricDrawStyle(orbitaPlaneta3, GLU_LINE);
            glRotatef(-30.0, 1, 0, 0);
            glColor3f(0.2, 0.5, 0.8);
            gluDisk(orbitaPlaneta2, 40.0, 40.0, 20, 20);  //rysowanie orbity
            glRotatef(30.0, 1, 0, 0);
            
        glPopMatrix();

        glPushMatrix(); //pocz planeta 1 i ksiezyc
        //ruch planety1 wokol slonca po orbicie 20 predkosc stopien/klatke
        glRotatef(0.1*(-katOrbitaPlaneta), 0, 1, 0);
        katOrbitaPlaneta += 0.25; //pred. kat. 0.25 stop/klatke CW
        glTranslatef(0.0, 0.0, 20.0);

        //planeta1
        glPushMatrix();
            glRotatef(0.1*katPlaneta, 0, 1, 0); //obrot planety1 wokol wlasnej osi
            katPlaneta ++; //spin planety 1 stop/klatke CW
            glColor3f(0.192, 0.529, 0.78);
            glRotatef(-90.0, 1, 0, 0);  //pionowa os
            glutWireSphere(2.0, 20, 10);    //promien planety 2.0
            //zainicjowanie dysku - orbity ksiezyca o promieniu 5
            orbitaKsiezyc1 = gluNewQuadric();
            gluQuadricDrawStyle(orbitaKsiezyc1, GLU_LINE);
            gluDisk(orbitaKsiezyc1, 5.0, 5.0, 20, 20);  //rysowanie orbity
        glPopMatrix();
        
        //ruch ksiezyca wokol planety1 po orbicie 5 predkosc stopien/klatke
        glRotatef(0.1*katOrbitaKsiezyc, 0, 1, 0);
        katOrbitaKsiezyc += 0.5; //pred. kat. ksiezyca 0.5 stop./klatke CCW
        glTranslatef(0.0, 0.0, 5.0);

        //ksiezyc
        glPushMatrix();
            glColor3f(0.7, 0.7, 0.7);
            glRotatef(-90.0, 1, 0, 0);  //pionowa os
            glutWireSphere(0.5, 20, 10);    //promien ksiezya 0.5
        glPopMatrix();

        glPopMatrix(); //koniec ksiezyc i planeta 1
            
        glPushMatrix(); //pocz planeta 2
        //ruch planety2 wokol slonca po orbicie 60 predkosc stopien/klatke
        glRotatef(45.0, 1, 0, 0);  //45 stopni OX
        glRotatef(0.1 * katOrbitaPlaneta2, 0, 1, 0);
        katOrbitaPlaneta2 += 0.25; //spin planety2 = 0.25 stop/klatke CCW
        glTranslatef(0.0, 0.0, 60.0);

        //Planeta 2
        glPushMatrix();
            glColor3f(0.8, 0.3, 0.5);
            glRotatef(90.0, 1, 0, 0);  //pionowa os
            glutWireSphere(4.0, 20, 10);    //promien planety 4.0
            
        glPopMatrix();

        glPopMatrix(); //koniec planeta 2
    
        glPushMatrix(); //pocz planeta 3
        //ruch planety3 wokol slonca po orbicie 40 predkosc stopien/klatke
        glRotatef(-30.0, 1, 0, 0);  //-30 stopni OX
        glRotatef(0.1 * (-katOrbitaPlaneta3), 0, 1, 0);
        katOrbitaPlaneta3 +=0.5; //spin planety3 = 0.5 stop/klatke CW
        glTranslatef(0.0, 0.0, 40.0);

        //Planeta 2
        glPushMatrix();
        glColor3f(0.2, 0.5, 0.8);
        glRotatef(90.0, 1, 0, 0);  //pionowa os
        glutWireSphere(8.0, 20, 10);    //promien planety 8.0

        glPopMatrix();

        glPopMatrix(); //koniec planeta 2


    glPopMatrix();

    // Usuniecie macierzy lezacej na  wierzcholku stosu (powrot do stanu
    // sprzed wywolania funkcji)
    glPopMatrix();

    // Przelaczenie buforow ramki
    glutSwapBuffers();


}

//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja ustawiajaca parametry rzutu perspektywicznego i rozmiary viewportu
void UstawParametryWidoku(int szerokosc, int wysokosc)
{
    // Ustawienie parametrow viewportu
    glViewport(0, 0, szerokosc, wysokosc);

    // Przejscie w tryb modyfikacji macierzy rzutowania
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (float)szerokosc / (float)wysokosc, 1.0, 1000.0);

    // Przejscie w tryb modyfikacji macierzy przeksztalcen geometrycznych
    glMatrixMode(GL_MODELVIEW);

    // Zmiana macierzy znajdujacej sie na wierzcholku stosu na macierz jednostkowa 
    glLoadIdentity();
}

//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja klawiszy specjalnych
void ObslugaKlawiszySpecjalnych(int klawisz, int x, int y)
{
    switch (klawisz)
    {
    //1_b zmiana oreintacji obserwatora bez ograniczen wzgledem OX i OY
    case GLUT_KEY_UP:
        rotObsX =  rotObsX + 1.0;
        break;

    case GLUT_KEY_DOWN:
        rotObsX = rotObsX - 1.0;
        break;

    case GLUT_KEY_LEFT:
        rotObsY = rotObsY - 1.0;
        break;

    case GLUT_KEY_RIGHT:
        rotObsY = rotObsY + 1.0;
        break;

    }
}
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja obslugi klawiatury
void ObslugaKlawiatury(unsigned char klawisz, int x, int y)
{

    switch (klawisz)
    {
    case '2':
        rotRamienia1 = (rotRamienia1 < 90.0) ? rotRamienia1 + 1.0 : rotRamienia1;
        break;

    case '@':
        rotRamienia1 = (rotRamienia1 > 0.0) ? rotRamienia1 - 1.0 : rotRamienia1;
        break;

    case '3':
        rotRamienia2 = (rotRamienia2 < 0.0) ? rotRamienia2 + 1.0 : rotRamienia2;
        break;

    case '#':
        rotRamienia2 = (rotRamienia2 > -90.0) ? rotRamienia2 - 1.0 : rotRamienia2;
        break;

    case '4':
        rotGlowicy = (rotGlowicy < 360.0) ? rotGlowicy + 1.0 : rotGlowicy;
        break;

    case '$':
        rotGlowicy = (rotGlowicy > 0.0) ? rotGlowicy - 1.0 : rotGlowicy;
        break;

    case '5':
        rozUchwytow = (rozUchwytow < 1.5) ? rozUchwytow + 0.1 : rozUchwytow;
        break;

    case '%':
        rozUchwytow = (rozUchwytow > 0.5) ? rozUchwytow - 0.1 : rozUchwytow;
        break;
    //1_a - mofyfikacja odkleglosci obserwatora: przyciski o i p
    //o-oddal obserwatora
    case 'o':
        odl_obs_od_obiektu = (odl_obs_od_obiektu < odl_max) ? odl_obs_od_obiektu + 1.0 : odl_obs_od_obiektu;
        break;
    //p-przybliz obserwatora
    case 'p':
        odl_obs_od_obiektu = (odl_obs_od_obiektu > odl_min) ? odl_obs_od_obiektu - 1.0 : odl_obs_od_obiektu;
        break;

    //1_b zmiana oreintacji obserwatora bez ograniczen wzgledem OZ za pomoc¹ z i Z (shift+z)
    case 'z':
        rotObsZ = rotObsZ + 1.0;
        break;

    case 'Z':
        rotObsZ = rotObsZ - 1.0;
        break;
    }

   

    /*if (klawisz == 27)
        return 0;*/
}

//////////////////////////////////////////////////////////////////////////////////////////
// Glowna funkcja programu
int  main(int argc, char** argv)
{
    // Zainicjowanie biblioteki GLUT
    glutInit(&argc, argv);

    // Ustawienie trybu wyswietlania
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Ustawienie polozenia dolenego lewego rogu okna
    glutInitWindowPosition(100, 100);

    // Ustawienie rozmiarow okna
    glutInitWindowSize(400, 400);

    // Utworzenie okna
    glutCreateWindow("Robot");

    // Odblokowanie bufora glebokosci
    glEnable(GL_DEPTH_TEST);

    // Ustawienie funkcji wykonywanej na danych w buforze glebokosci
    glDepthFunc(GL_LEQUAL);

    // Ustawienie wartosci czyszczacej zawartosc bufora glebokosci
    glClearDepth(1000.0);

    // Ustawienie koloru czyszczenia bufora ramki kolor tla 0.2 0.2 0.2 - szary
    glClearColor(0.2, 0.2, 0.2, 0.0);

    // Zarejestrowanie funkcji (callback) wyswietlajacej
    glutDisplayFunc(WyswietlObraz);

    // Zarejestrowanie funkcji (callback) wywolywanej za kazdym razem kiedy
    // zmieniane sa rozmiary okna
    glutReshapeFunc(UstawParametryWidoku);

    // Zarejestrowanie funkcji wykonywanej gdy okno nie obsluguje
    // zadnych zadan
    glutIdleFunc(WyswietlObraz);

    // Zarejestrowanie funkcji obslugi klawiatury
    glutKeyboardFunc(ObslugaKlawiatury);

    // Zarejestrowanie funkcji obslugi klawiszy specjalnych
    glutSpecialFunc(ObslugaKlawiszySpecjalnych);


    // Zainicjowanie kwadryk tworzacych ramie robota
    InicjujRamieRobota();

    // Obsluga glownej petli programu (wywolywanie zarejestrowanych callbackow
    // w odpowiedzi na odbierane zdarzenia lub obsluga stanu bezczynnosci)
    glutMainLoop();

    return 0;


}

