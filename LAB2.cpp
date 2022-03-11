#include <iostream>
#include <vector>
using namespace std;

void make_ref(int** v, int n)
{
	for (int i = 0; i < n; i++)
		v[i][i] = 1;
}

void make_sim(int** v, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (v[i][j] == 1)
				v[j][i] = 1;
}

void make_tran(int** v, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (v[j][k] == 1) {
					for (int p = 0; p < n; p++) {
						if (v[k][p] == 1)
							v[j][p] = 1;
					}
				}
			}
		}
	}
}

void eq(int** v, int n) {
	int** v2;
	v2 = new int* [n];
	for (int i = 0; i < n; i++) {
		v2[i] = new int[n];
		for (int j = 0; j < n; j++) {
			v2[i][j] = v[i][j];
		}
	}

	make_ref(v2, n);
	make_sim(v2, n);
	make_tran(v2, n);
	cout << endl << "Замыкание эквивалентности:" << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << v2[i][j] << ' ';
		cout << endl;
	}
	vector<vector<int>> res;
	int* count = new int[n];
	for (int i = 0; i < n; i++) {
		count[i] = 1;
	}

	for (int i = 0; i < n; i++) {
		if (count[i]) {
			vector<int> srez;
			for (int j = i; j < n; j++) {
				if (v2[i][j] && count[j]) {
					count[j] = 0;
					srez.push_back(j);
				}
			}
			count[i] = 0;
			res.push_back(srez);
		}
	}

	cout << endl << "Фактор-множество: {";
	for (int i = 0; i < res.size(); i++) {
		cout << "{";
		for (int j = 0; j < res[i].size(); j++) {
			cout << res[i][j] + 1;
			if (j != res[i].size() - 1)
				cout << ", ";
		}
		cout << "}";
		if (i != res.size() - 1)
			cout << ", ";
	}
	cout << "}" << endl;

	cout << "Система представителей фактор-множества: {";
	for (int i = 0; i < res.size(); i++) {
		cout << res[i][0] + 1;
		if (i != res.size() - 1)
			cout << ", ";
	}
	cout << "}" << endl << endl;
}



vector <pair <int, int> > find_all_min(vector <int> v) {
	vector <pair<int, int> > res;
	res.push_back(make_pair(v[0], 0));
	for (int i = 1; i < v.size(); i++) {
		int checker = 0;
		for (int j = 0; j < res.size(); j++)
			if (v[i] % res[j].first == 0)
				checker++;
		if (checker == 0)
			res.push_back(make_pair(v[i], i));
	}
	return res;
}


void hasse(vector <int> v) {
	vector <vector <int>> res;
	int lvl = 0;
	while (v.size() > 0) {
		vector <pair<int, int>> A_i = find_all_min(v);
		vector <int> help;
		for (int i = A_i.size() - 1; i >= 0; i--) {
			v.erase(v.begin() + A_i[i].second);
			help.push_back(A_i[i].first);
		}
		res.push_back(help);
		lvl++;
	}
	for (int i = res.size() - 1; i >= 0; i--) {
		for (int j = 0; j < res[i].size(); j++) {
			cout << res[i][j] << " ";
		}
		cout << endl;
	}
	vector <pair<int, int>> res_pairs;
	for (int i = res.size() - 1; i > 0; i--) {
		for (int j = 0; j < res[i].size(); j++) {
			for (int k = 0; k < res[i - 1].size(); k++) {
				if (res[i][j] % res[i - 1][k] == 0) {
					res_pairs.push_back(make_pair(res[i][j], res[i - 1][k]));
				}
			}
		}
	}
	cout << endl;
	for (int i = 0; i < res_pairs.size(); i++) {
		cout << '(' << res_pairs[i].first << ", " << res_pairs[i].second << ")";
		if (i < res_pairs.size() - 1) cout << ", ";
	}
	cout << endl;
}


vector <int> find_all(int x, int one) {
	vector <int> res;
	for (int i = 2 - one; i < x / 2.0 + 1; i++) {
		if (x % i == 0)
			res.push_back(i);
	}
	res.push_back(x);
	return res;
}


vector <int> find_all_min_matr(vector <vector <int>> v, int n) {
	vector <int> res;
	for (int i = 0; i < n; i++) {
		if (v[i][i] > -1) {
			int checker = 0;
			for (int j = 0; j < n; j++)
				if (v[j][i] == 1)
					if (i != j)
						checker++;
			if (checker == 0)
				res.push_back(i);
		}
	}
	return res;
}


vector <int> find_all_max_matr(vector <vector <int>> v, int n) {
	vector <int> res;
	for (int i = 0; i < n; i++) {
		int checker = 0;
		for (int j = 0; j < n; j++)
			if (v[i][j])
				if (i != j)
					checker++;
		if (checker == 0)
			res.push_back(i);
	}
	return res;
}

void hasse_pair(vector <vector <int>> v, int n, vector <vector <int>> hasse_diag) {
	vector <pair<int, int>> res;
	for (int i = hasse_diag.size() - 1; i > 0; i--)
		for (int j = 0; j < hasse_diag[i].size(); j++)
			for (int k = 0; k < hasse_diag[i - 1].size(); k++)
				if (v[hasse_diag[i - 1][k]][hasse_diag[i][j]])
					res.push_back(make_pair(hasse_diag[i - 1][k] + 1, hasse_diag[i][j] + 1));

	for (int i = 0; i < res.size(); i++) {
		cout << "(" << res[i].first << ", " << res[i].second << ")";
		if (i != res.size() - 1) cout << ",  ";
		else cout << endl << endl;
	}
}

void hasse_matr(vector <vector <int>> v_real, int n) {
	vector <vector <int>> v;
	v.resize(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			v[i].push_back(v_real[i][j]);
	}
	vector <vector <int>> res;
	while (true) {
		vector <int> A_i = find_all_min_matr(v, n);
		if (A_i.size() == 0)
			break;
		vector <int> help;
		for (int k = A_i.size() - 1; k >= 0; k--) {
			for (int i = v.size() - 1; i >= 0; i--) {
				for (int j = v[i].size() - 1; j >= 0; j--) {
					if (A_i[k] == j)
						v[i][j] = -1;
				}
				if (A_i[k] == i) {
					for (int j = v[i].size() - 1; j >= 0; j--)
						v[i][j] = -1;
				}
			}
			help.push_back(A_i[k]);
		}
		res.push_back(help);
	}
	for (int i = res.size() - 1; i >= 0; i--) {
		for (int j = 0; j < res[i].size(); j++) {
			cout << res[i][j] + 1 << " ";
		}
		cout << endl;
	}

	hasse_pair(v_real, n, res);
}




vector<int> p(vector<int> v1, vector<int> v2) {
	vector<int> res;
	for (int i = 0; i < v1.size(); i++)
		for (int j = 0; j < v2.size(); j++)
			if (v1[i] == v2[j])
				res.push_back(v1[i]);
	return res;
}

bool checker(vector<vector<int>> v1, vector<int> v2) {
	for (int i = 0; i < v1.size(); i++) {
		if (v1[i].size() == v2.size()) {
			int a = v2.size();
			for (int j = 0; j < v1[i].size(); j++) {
				if (v1[i][j] == v2[j])
					a--;
			}
			if (a == 0)
				return false;
		}
	}
	return true;
}



vector <pair<vector <int>, int>> find_all_min_zfg(vector<vector<int>> v) {
	vector <pair<vector <int>, int>> res;
	for (int i = 0; i < v.size(); i++) {
		int count = 0;
		for (int j = 0; j < v.size(); j++) {
			if (p(v[i], v[j]) == v[i] || p(v[i], v[j]) != v[j]) {
				count++;
			}
		}
		if (count == v.size())
			res.push_back(make_pair(v[i], i));
	}
	return res;
}

vector<int> fi(int** matr, int x, int n) {
	vector<int> res;
	for (int i = 0; i < n; i++) {
		if (matr[x][i])
			res.push_back(i);
	}
	return res;
}

void c(vector<vector<vector<int>>> v, int** matr, int n) {
	char alf[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o' };
	vector<vector<pair<vector<int>, vector<int>>>> res;
	res.resize(v.size());
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			vector<int> count;
			int checker = 0;
			for (int k = 0; k < v[i][j].size(); k++) {
				checker++;
				if (k == 0)
					count = fi(matr, v[i][j][k], n);
				else
					count = p(count, fi(matr, v[i][j][k], n));
			}
			if (checker > 0)
				res[i].push_back(make_pair(v[i][j], count));
			else {
				vector<int> help;
				for (int i = 0; i < n; i++)
					help.push_back(i);
				res[i].push_back(make_pair(v[i][j], help));
			}
		}
	}
	cout << endl << "Диаграмма Хассе решётки концептов:" << endl;
	for (int i = res.size() - 1; i >= 0; i--) {
		for (int j = 0; j < res[i].size(); j++) {
			cout << "({";
			for (int k = 0; k < res[i][j].first.size(); k++) {
				cout << res[i][j].first[k] + 1;
				if (k != res[i][j].first.size() - 1) cout << ", ";
			}
			cout << "}, {";
			for (int k = 0; k < res[i][j].second.size(); k++) {
				cout << alf[res[i][j].second[k]];
				if (k != res[i][j].second.size() - 1) cout << ", ";
			}
			cout << "})  ";
		}
		cout << endl;
	}
}


void hasse_zfg(vector<vector<int>> v, int** matr, int n) {
	vector<vector<vector<int>>> res;
	int lvl = 0;
	while (v.size() > 0) {
		vector <pair<vector <int>, int>> A_i = find_all_min_zfg(v);
		vector<vector<int>> help;
		for (int i = A_i.size() - 1; i >= 0; i--) {
			v.erase(v.begin() + A_i[i].second);
			help.push_back(A_i[i].first);
		}
		res.push_back(help);
		lvl++;
	}
	cout << "Диаграмма Хассе системы замыкания " << endl;
	for (int i = res.size() - 1; i >= 0; i--) {
		for (int j = 0; j < res[i].size(); j++) {
			cout << "{";
			for (int k = 0; k < res[i][j].size(); k++) {
				cout << res[i][j][k] + 1;
				if (k != res[i][j].size() - 1) cout << ", ";
			}
			cout << "}  ";
		}
		cout << endl;
	}

	vector<pair<vector<int>, vector<int>>> res_pairs;
	for (int i = 0; i < res.size() - 1; i++) {
		for (int j = 0; j < res[i].size(); j++) {
			for (int k = 0; k < res[i + 1].size(); k++) {
				if (p(res[i][j], res[i + 1][k]) == res[i][j]) {
					res_pairs.push_back(make_pair(res[i][j], res[i + 1][k]));
				}
			}
		}
	}

	cout << endl;
	for (int i = 0; i < res_pairs.size(); i++) {
		cout << "({";
		for (int j = 0; j < res_pairs[i].first.size(); j++) {
			cout << res_pairs[i].first[j] + 1;
			if (j != res_pairs[i].first.size() - 1)
				cout << ", ";
		}
		cout << "}";
		cout << ", {";
		for (int j = 0; j < res_pairs[i].second.size(); j++) {
			cout << res_pairs[i].second[j] + 1;
			if (j != res_pairs[i].second.size() - 1)
				cout << ", ";
		}
		cout << "}";

		cout << ")";
		if (i != res_pairs.size() - 1)
			cout << ", " << endl;
	}
	cout << endl << endl;

	c(res, matr, n);
}



vector<vector<int>> zfg(int** v, int n) {
	vector<vector<int>> res;
	vector<int> G;
	for (int i = 0; i < n; i++)
		G.push_back(i);
	res.push_back(G);

	for (int i = 0; i < n; i++) {
		vector<int> count;
		for (int j = 0; j < n; j++) {
			if (v[j][i])
				count.push_back(j);
		}
		if (checker(res, count))
			res.push_back(count);
		for (int i = 0; i < res.size(); i++) {
			vector<int> new_count = p(res[i], count);
			if (checker(res, new_count))
				res.push_back(new_count);
		}
	}

	cout << endl << "Система замыканий на множестве объектов:" << endl << "{";
	for (int i = 0; i < res.size(); i++) {
		cout << "{";
		for (int j = 0; j < res[i].size(); j++) {
			cout << res[i][j] + 1;
			if (j != res[i].size() - 1)
				cout << ", ";
		}
		cout << "}";
		if (i != res.size() - 1)
			cout << ", ";
	}
	cout << "}" << endl << endl;

	hasse_zfg(res, v, n);

	return res;
}






int main()
{
	setlocale(LC_ALL, "Russian");
	int h = -1;
	while (h != 0)
	{
		cout << "1 - Порядок. Целое число, включая единицу" << endl;
		cout << "2 - Порядок. Целое число, не включая единицу" << endl;
		cout << "3 - Порядок. Матрица порядка " << endl;
		cout << "4 - Построение эквивалентного замыкания бинарного отношения и системы представителей фактор-множества " << endl;
		cout << "5 - Вычисление решетки концептов" << endl;
		cout << "0 - Выход" << endl;
		cin >> h;

		if (h == 1) {
			int x;
			cout << "Введите число" << endl;
			cin >> x;
			cout << endl;
			vector <int> res = find_all(x, 1);
			vector <pair<int, int>> min = find_all_min(res);
			cout << endl << "Минимальные элементы: ";
			for (int i = 0; i < min.size(); i++) {
				cout << min[i].first;
				if (i < min.size() - 1) cout << ", ";
			}
			cout << endl;
			if (min.size() == 1) cout << "Наименьший элемент: " << min[0].first << endl;
			else cout << "Наименьшего элемента нет" << endl;

			cout << "Максимальные элементы: " << x << endl;
			cout << "Наибольший элемент: " << x << endl;

			hasse(res);
		}
		if (h == 2) {
			int x;
			cout << "Введите число" << endl;
			cin >> x;
			cout << endl;
			vector <int> res = find_all(x, 0);
			vector <pair<int, int>> min = find_all_min(res);
			cout << endl << "Минимальные элементы: ";
			for (int i = 0; i < min.size(); i++) {
				cout << min[i].first;
				if (i < min.size() - 1) cout << ", ";
			}
			cout << endl;
			if (min.size() == 1) cout << "Наименьший элемент: " << min[0].first << endl;
			else cout << "Наименьшего элемента нет" << endl;

			cout << "Максимальные элементы: " << x << endl;
			cout << "Наибольший элемент: " << x << endl;

			hasse(res);
		}
		if (h == 3) {
			int n;
			cout << "Введите количество элементов. n = ";
			cin >> n;
			vector <vector <int>> v;
			v.resize(n);
			cout << "Введите матрицу бинарного отношения. А = " << endl;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					int x_cin;
					cin >> x_cin;
					v[i].push_back(x_cin);
				}
			}
			vector <int> min = find_all_min_matr(v, n);
			vector <int> max = find_all_max_matr(v, n);

			cout << endl << "Минимальные элементы: ";
			for (int i = 0; i < min.size(); i++) {
				cout << min[i] + 1;
				if (i < min.size() - 1) cout << ", ";
			}
			cout << endl;
			if (min.size() == 1) cout << "Наименьший элемент: " << min[0] + 1 << endl;
			else cout << "Наименьшего элемента нет" << endl;

			cout << "Максимальные элементы: ";
			for (int i = 0; i < max.size(); i++) {
				cout << max[i] + 1;
				if (i < max.size() - 1) cout << ", ";
			}
			cout << endl;
			if (max.size() == 1) cout << "Наибольший элемент: " << max[0] + 1 << endl;
			else cout << "Наибольшего элемента нет" << endl;
			cout << endl;
			hasse_matr(v, n);
		}
		if (h == 4) {
			int n;
			cout << "Введите количество элементов. n = ";
			cin >> n;
			int** v;
			v = new int* [n];
			cout << "Введите матрицу бинарного отношения. А = " << endl;
			for (int i = 0; i < n; i++) {
				v[i] = new int[n];
				for (int j = 0; j < n; j++) {
					cin >> v[i][j];
				}
			}
			eq(v, n);
		}
		if (h == 5) {
			int n;
			cout << "Введите количество атрибутов и объектов. n = ";
			cin >> n;
			int** v;
			v = new int* [n];
			cout << "Введите матрицу. А = " << endl;
			for (int i = 0; i < n; i++) {
				v[i] = new int[n];
				for (int j = 0; j < n; j++) {
					cin >> v[i][j];
				}
			}
			zfg(v, n);
		}
		cout << endl << endl;
	}

	return 0;
}