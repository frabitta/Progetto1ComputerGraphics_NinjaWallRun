#include "geometrie.h"

/* legge i dati dei file contenenti i modelli di curva*/
void readCurvaModelFile(vector<vec2>& cp_ver, vector<vec4>& cp_col, const char* curvaFileName, vec2& centerPoint, vec4& centerColor);
/* genera i punti di curva*/
void InterpolazioneHermite(vector<vec3>& vertici, vector<vec4>& colori, vector<vec2> cp_ver, vector<vec4> cp_col, float* t, float step);


void init_plane(vector<vec3> &vertici, vector<vec4> &colori, vec2 btm_left, vec2 top_right, vec4 color)
{
	vertici.clear();
	colori.clear();

	vertici.push_back(vec3(btm_left.x, btm_left.y, 0.));
	vertici.push_back(vec3(top_right.x, btm_left.y, 0.));
	vertici.push_back(vec3(top_right.x, top_right.y, 0.));
	vertici.push_back(vec3(btm_left.x, top_right.y, 0.));

	colori.push_back(color);
	colori.push_back(color);
	colori.push_back(color);
	colori.push_back(color);
}

void init_triangle(vector<vec3>& vertici, vector<vec4>& colori) {
	vertici.clear();
	vertici.push_back(vec3(-1, -1, 0));
	vertici.push_back(vec3(1, -1, 0));
	vertici.push_back(vec3(0, 1, 0));
	colori.clear();
	colori.push_back(vec4(0, 0, 0, 1));
	colori.push_back(vec4(0, 0, 0, 1));
	colori.push_back(vec4(1, 0, 0, 1));
}

void init_curvaHModel(vector<vec3>& vertici, vector<vec4>& colori, const char* curvaFileName)
{
	vector<vec2> cp_ver;
	vector<vec4> cp_col;
	vec2 centerPoint;
	vec4 centerColor;

	readCurvaModelFile(cp_ver, cp_col, curvaFileName, centerPoint, centerColor);

	// se ha successo il caricamento allora svuotiamo
	vertici.clear();
	colori.clear();

	// inserisco il punto centrale
	vertici.push_back(vec3(centerPoint.x, centerPoint.y, 0.));
	colori.push_back(centerColor);
	int n_cp = cp_ver.size();

	// assegno i cp ad un valore del parametro t
	float *t = (float *)malloc(sizeof(*t) * n_cp);
	if (t == NULL) {
		perror("ERRORE: impossibile allocare memoria");
		return;
	}

	float cp_step = 1.0 / (n_cp - 1);
	for (int i = 0; i < n_cp - 1;  i++) {
		t[i] = cp_step * i;
	}
	t[n_cp - 1] = 1.0;

	// inserisco i punti del contorno
	float step_Pointsdensity = 0.01;
	InterpolazioneHermite(vertici, colori, cp_ver, cp_col, t, step_Pointsdensity);

	free(t);
}





void readCurvaModelFile(vector<vec2>& cp_ver, vector<vec4>& cp_col, const char* curvaFileName, vec2 &centerPoint, vec4 &centerColor) {
	char curvaPath[100] = CURVE_FOLDER;
	strcat_s(curvaPath, curvaFileName);
	FILE* f;
	fopen_s(&f, curvaPath, "r");

	if (f == NULL) {
		perror("ERRORE: Impossibile aprire il file");
		return;
	}

	int n_cp;
	if (!fscanf_s(f, "%d", &n_cp)) {
		perror("ERRORE: Impossibile leggere il file");
	}

	float v_x, v_y;
	float c_r, c_g, c_b, c_a;
	if (!fscanf_s(f, "%f %f %f %f %f %f", &v_x, &v_y, &c_r, &c_g, &c_b, &c_a)) {
		perror("ERRORE: Impossibile leggere il file");
	}
	centerPoint = vec2(v_x, v_y);
	centerColor = vec4(c_r, c_g, c_b, c_a);

	for (int i = 0; i < n_cp; i++) {
		if (!fscanf_s(f, "%f %f %f %f %f %f", &v_x, &v_y, &c_r, &c_g, &c_b, &c_a)) {
			perror("ERRORE: Impossibile leggere il file");
		}
		vec2 punto = vec2(v_x, v_y);
		vec4 colore = vec4(c_r, c_g, c_b, c_a);
		cp_ver.push_back(punto);
		cp_col.push_back(colore);
	}

	fclose(f);
}

/// /////////////////////////////////// Disegna geometria //////////////////////////////////////
//Per Curve di hermite
#define PHI0(t)  (2.0*t*t*t-3.0*t*t+1)
#define PHI1(t)  (t*t*t-2.0*t*t+t)
#define PSI0(t)  (-2.0*t*t*t+3.0*t*t)
#define PSI1(t)  (t*t*t-t*t)

float dx0(int i, float* t, vector<vec2> cp_ver) {
	if (i == 0)
		return  0.5 * (cp_ver[i + 1].x - cp_ver[i].x) / (t[i + 1] - t[i]);
	if (i == cp_ver.size() - 1)
		return  0.5 * (cp_ver[i].x - cp_ver[i - 1].x) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return  0.5 * (cp_ver[i].x - cp_ver[i - 1].x) / (t[i] - t[i - 1]) + 0.5 * (cp_ver[i + 1].x - cp_ver[i].x) / (t[i + 1] - t[i]);
	else
		return  0.5 * (cp_ver[i].x - cp_ver[i - 1].x) / (t[i] - t[i - 1]) + 0.5 * (cp_ver[i + 1].x - cp_ver[i].x) / (t[i + 1] - t[i]);
}
float dy0(int i, float* t, vector<vec2> cp_ver)
{
	if (i == 0)
		return 0.5 * (cp_ver[i + 1].y - cp_ver[i].y) / (t[i + 1] - t[i]);
	if (i == cp_ver.size() - 1)
		return  0.5 * (cp_ver[i].y - cp_ver[i - 1].y) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return  0.5 * (cp_ver[i].y - cp_ver[i - 1].y) / (t[i] - t[i - 1]) + 0.5 * (cp_ver[i + 1].y - cp_ver[i].y) / (t[i + 1] - t[i]);
	else
		return  0.5 * (cp_ver[i].y - cp_ver[i - 1].y) / (t[i] - t[i - 1]) + 0.5 * (cp_ver[i + 1].y - cp_ver[i].y) / (t[i + 1] - t[i]);
}

void InterpolazioneHermite(vector<vec3>& vertici, vector<vec4>& colori, vector<vec2> cp_ver, vector<vec4> cp_col, float* t, float step)
{
	float tg;

	int is = 0;
	float ampiezza = t[is + 1] - t[is];
	for (tg = 0; tg < 1.0; tg += step) {
		// localizzare tg nell'intervallo [t[is], t[is+1]]
		// int i = localize_t(t, tg, curva->ncp); // studio tutta la curva per trovare l'intervallo
		if (tg > t[is + 1]) {	// se sono finito nell'intervallo successivo aggiorno, altrimenti sono ancora nello stesso intervallo
			is++;
			ampiezza = t[is + 1] - t[is];
		}

		// mappo tg appartenente a [t[is], t[is+1]] in [0,1] -> ottengo tm
		float tm = (tg - t[is]) / ampiezza;

		// valuto x, y
		float x = cp_ver[is].x * PHI0(tm) + cp_ver[is + 1].x * PSI0(tm) + dx0(is, t, cp_ver) * PHI1(tm) * ampiezza + dx0(is + 1, t, cp_ver) * PSI1(tm) * ampiezza;
		float y = cp_ver[is].y * PHI0(tm) + cp_ver[is + 1].y * PSI0(tm) + dy0(is, t, cp_ver) * PHI1(tm) * ampiezza + dy0(is + 1, t, cp_ver) * PSI1(tm) * ampiezza;

		// colore interpolato tra i due cp
		vec4 interpolatedColor = mix(cp_col[is], cp_col[is+1], tm);

		vertici.push_back(vec3(x, y, 0.0));
		colori.push_back(interpolatedColor);
	}
	
	int last = cp_ver.size() - 1;
	vec2 lastPoint = cp_ver[last];
	vertici.push_back(vec3(lastPoint.x, lastPoint.y, 0.0));
	colori.push_back(cp_col[last]);


}