
out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//Zmienne interpolowane
in vec4 iC; //Kolor wyliczony w vertex shaderze


void main(void)
{
    pixelColor=iC;
}
