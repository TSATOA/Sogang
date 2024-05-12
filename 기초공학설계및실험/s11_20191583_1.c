#include<stdio.h>

float weightSum(int *five_ago, int *four_ago, int *three_ago, int *two_ago, int *one_ago);
void printBySection(float weight_sum);

int main()
{
	int five_ago, four_ago, three_ago, two_ago, one_ago;
	scanf("%d%d%d%d%d", &five_ago, &four_ago, &three_ago, &two_ago, &one_ago);
	printBySection(weightSum(&five_ago, &four_ago, &three_ago, &two_ago, &one_ago));
	return 0;
}

float weightSum(int *five_ago, int *four_ago, int *three_ago, int *two_ago, int *one_ago) {
	float total;
	total = (float)(*five_ago)*0.04 + (*four_ago)*0.06 + (*three_ago)*0.15 + (*two_ago)*0.25 + (*one_ago)*0.5;
	return total;
}

void printBySection(float weight_sum) {
	printf("%.2f ", weight_sum);
	if (weight_sum >= 0 && weight_sum < 0)
		printf("good");
	if (weight_sum >= 30 && weight_sum < 80)
		printf("normal");
	if (weight_sum >= 80 && weight_sum < 150)
		printf("bad");
	if (weight_sum >= 150)
		printf("very bad");
	return;
}