#include <stdio.h>
const double RateKphMph = 1.609344;
void main()
{
	int kph;
	double mph;

	printf("����� ������ �Է��Ͻÿ�[Km/H]: ");
	scanf("%d", &kph);
	mph = kph / RateKphMph;
	printf("����� ������ %lf [MPH] �Դϴ�.\n", mph);
}