#include<stdio.h>
#include<math.h>
#include<cmath>
#include<float.h>

void merge(double *X, unsigned *Xid, unsigned *TMP, unsigned left, unsigned mid, unsigned right) {
	unsigned i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;
	while (i <= mid && j <= right) {
		if (X[Xid[i]] <= X[Xid[j]])
			TMP[k++] = Xid[i++];
		else
			TMP[k++] = Xid[j++];
	}
	if (i > mid) {
		for (l = j; l <= right; l++)
			TMP[k++] = Xid[l];
	}
	else {
		for (l = i; l <= mid; l++)
			TMP[k++] = Xid[l];
	}
	for (i = left; i <= right; i++) {
		Xid[i] = TMP[i];
	}
}

void mergeSort(double *X, unsigned *Xid, unsigned *TMP, unsigned left, unsigned right) {
	unsigned mid;
	if (left < right) {
		mid = (left + right) / 2;
		mergeSort(X, Xid, TMP, left, mid);
		mergeSort(X, Xid, TMP, mid + 1, right);
		merge(X, Xid, TMP, left, mid, right);
	}
}

void   sortXid(double *X, unsigned *Xid, unsigned *TMP, unsigned N) {
	mergeSort(X, Xid, TMP, 0, N - 1);
}


/*ClosestPair*/

//ClosestPair를 구현하기 위한 추가 함수들
//dist함수(Euclidean distance)
double dist(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

//bruteForce
double bruteForce(double *X, double *Y, unsigned *Xid, unsigned *Yid, unsigned L, unsigned R, unsigned *pt1, unsigned *pt2, unsigned *TMP) {
	double min = DBL_MAX;
	for (unsigned i = L; i <= R; i++) {
		Yid[i] = Xid[i];
	}
	unsigned k;
	for (unsigned i = L; i <= R; i++) {
		for (unsigned j = L; j <= R -1; j++) {
			if (Y[Yid[j]] > Y[Yid[j + 1]]) {
				k = Yid[j+1];
				Yid[j+1] = Yid[j];
				Yid[j] = k;
			}
		}
	}
	for (unsigned i = L; i <= R-1; i++) {
		for (unsigned j = i + 1; j <= R; j++) {
			if (dist(X[Xid[i]], Y[Xid[i]], X[Xid[j]], Y[Xid[j]]) < min) {
				min = dist(X[Xid[i]], Y[Xid[i]], X[Xid[j]], Y[Xid[j]]);
				*pt1 = Xid[i];
				*pt2 = Xid[j];
			}
		}
	}
	
	return min;
}


double closestPairDC(
	unsigned L, unsigned R,	  // current leftmost and rightmost indices
	unsigned *pt1, unsigned *pt2, // closest pair points indices
	double *X, double *Y,         // (x,y) positions array(input)
	unsigned *Xid,  // point index array(sorted by x coordinates)
	unsigned *Yid,  // point index array(gradually sorted by y coordinates)
	unsigned *TMP,  // temporal index array
	unsigned THR	// threshold value
) {
	
	if (R - L <= THR) {
		return bruteForce(X, Y, Xid, Yid, L, R, pt1, pt2, TMP);
	}
	unsigned mid = (R + L) / 2;
	unsigned N = R - L + 1;
	double dl = closestPairDC(L, mid, pt1, pt2, X, Y, Xid, Yid, TMP, THR);
	unsigned ptl1 = *pt1;
	unsigned ptl2 = *pt2;
	double dr = closestPairDC(mid + 1, R, pt1, pt2, X, Y, Xid, Yid, TMP, THR);
	merge(Y, Yid, TMP, L, mid, R);
	
	double dlr;
	if (dl > dr) {
		dlr = dr;
	}
	else {
		dlr = dl;
		*pt1 = ptl1;
		*pt2 = ptl2;
	}
	
	
	double Xmid = (X[Xid[mid]] + X[Xid[mid + 1]]) / 2;
	
	unsigned k = 1;
	for (unsigned i = L; i <= R; i++) {
		if (X[Yid[i]] > Xmid) {
			if (X[Yid[i]] - Xmid < dlr) {
				TMP[k] = Yid[i];
				k++;
			}
		}
		else {
			if (Xmid - X[Yid[i]]< dlr) {
				TMP[k] = Yid[i];
				k++;
			}
		}
	}
	
	
	
	double dij = DBL_MAX;
	


	for (unsigned i = 1; i < k-1; i++) {
		for (unsigned j = i + 1; j < k; j++) {
			if (Y[TMP[j]] - Y[TMP[i]]>dlr) break;
			if (dist(X[TMP[j]], Y[TMP[j]], X[TMP[i]], Y[TMP[i]])<dij) {
				dij = dist(X[TMP[j]], Y[TMP[j]], X[TMP[i]], Y[TMP[i]]);
				ptl1 = TMP[i];
				ptl2 = TMP[j];
			}
		}
	}
	
	if (dij < dlr) {
		dlr = dij;
		*pt1 = ptl1;
		*pt2 = ptl2;
	}
	
	return dlr;
}
