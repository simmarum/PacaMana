

//Zmienne jednorodne
uniform mat4 P; //Macierz rzutowania
uniform mat4 V; //Macierz widoku
uniform mat4 M; //Macierz modelu
uniform vec4 lp; //polozenie zrodla swiatla, wyrazone w przestrzeni swiata

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka, wyrazone w przestrzeni modelu
in vec4 color;  //kolor wierzcholka
in vec4 normal; //wektor normalny w wierzcholku, wyrazone w przestrzeni modelu

//Zmienne interpolowane
out vec4 iC; //Kolor wyliczany przez vertex shader dla kazdego wierzcholka, pozniej interpolowany dla kazdego piksela

void main(void) {
    //Ponizej zakodowane na twardo wlasnosci materialu i kolory swiatla (zeby nie komplikowac kodu)
    vec4 ka=vec4(0,0,0,0); //Kolor materialu dla swiatla otoczenia
    vec4 kd=color;         //Kolor materialu dla swiatla rozproszonego
    vec4 la=vec4(0,0,0,1); //Kolor swiatla otoczenia
    vec4 ld=vec4(1,1,1,1); //Kolor swiatla rozpraszanego

    //Obliczenie wektora do swiatla
    vec4 l=normalize(V*(lp-M*vertex));//Wektor do swiatla w przestrzeni oka
	//Obliczenie wektora normalnego
    vec4 n=normalize(V*M*normal); //Wektor normalny w przestrzeni oka

    //Obliczenie iloczynu skalarnego  wektorów l i n
    float nl=max(dot(n,l),0);

    //Obliczenie modelu oswietlenia
    iC=ka*la+kd*ld*vec4(nl,nl,nl,1);

	//Obliczenie wspolrzednej wierzcholka w przestrzeni przyciecia
	gl_Position=P*V*M*vertex;
}


