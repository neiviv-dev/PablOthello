#include <wx/wx.h>
#include <wx/grid.h>
#include "fenetre.h"
#include "vector"
#include <random>
#include "menu.h"

enum {ID_TEXT = 1,ID_NvllPartie = 2,ID_TEXTJ1 = 3,ID_TEXTJ2 = 4,ID_USERJ1 = 5,ID_IAJ1 = 6,ID_IA2J1 = 7,TIMER = 8,ID_USERJ2 = 9,ID_IAJ2 = 10,ID_IA2J2 = 11,ID_IA3J1 = 12,ID_IA3J2 = 13};

Fenetre::Fenetre(const wxString& title) 
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1500, 1000),wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER) {
    Centre();
    vector<int> Score = j.g.getScore();
    int n = j.g.n;
    PanelJ1 = new wxPanel(this,
                            wxID_ANY,
                            wxPoint(0, 0),
                            wxSize(300, 1000));
    PanelJ1->SetBackgroundColour(wxColour(158, 188, 161));
    // Set panel background image
    
    cactus_blanc = new wxStaticBitmap( PanelJ1, wxID_ANY, wxBitmap("../Images/cactus_blancv2.png", wxBITMAP_TYPE_PNG), wxPoint(0,0), wxSize(300, 1000));
    


    PanelJ2 = new wxPanel(this,
                            wxID_ANY,
                            wxPoint(1200, 0),
                            wxSize(300, 1000));
    PanelJ2->SetBackgroundColour(wxColour(158, 188, 161));

    cactus_noir = new wxStaticBitmap( PanelJ2, wxID_ANY, wxBitmap("../Images/cactus_noirv2.png", wxBITMAP_TYPE_PNG), wxPoint(0,0), wxSize(300, 1000));
    Plateau = new wxPanel(this,
                            wxID_ANY,
                            wxPoint(300, 0),
                            wxSize(900, 1000));
    Plateau->SetBackgroundColour(wxColour(2, 36, 19));


    text = new wxStaticText(Plateau,
                            ID_TEXT,
                            wxString("Au tour de J2 (Noir)"),
                            wxPoint(300, 100),
                            wxSize(300, 1000));
    text->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    text->SetForegroundColour(wxColour(* wxWHITE));
    


    textJ1 = new wxStaticText(PanelJ1,
                            ID_TEXTJ1,
                            wxString::Format(wxT("Score J1 :\n   %d"), Score[1]),
                            wxPoint(90, 700),
                            wxSize(300, 1000));
    wxFont font( 20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    textJ1->SetFont(font);

    textJ2 = new wxStaticText(PanelJ2,
                            ID_TEXTJ2,
                            wxString::Format(wxT("Score J2 :\n   %d"), Score[0]),
                            wxPoint(90, 700),
                            wxSize(300, 1000));
    textJ2->SetFont(font);
    
    grid = new wxGrid(Plateau, wxID_ANY, wxPoint(150, 200), wxSize(600, 600));
    
    grid->CreateGrid( n, n );
    grid->SetRowLabelSize(0);
    grid->SetColLabelSize(0);
    grid->EnableEditing(false);
    grid->EnableDragGridSize(false);
    grid->EnableDragColSize(false);
    grid->EnableDragRowSize(false);

    
    nouvellePartie = new wxButton(Plateau,
                            ID_NvllPartie,
                            wxString("Nouvelle Partie"),
                            wxPoint(300, 850),
                            wxSize(300, 50));

    userJ1 = new wxButton(Plateau,
                            ID_USERJ1,
                            wxString("Humain"),
                            wxPoint(25, 425),
                            wxSize(100, 50));
    userJ1->SetBackgroundColour(wxColour(* wxRED));

    iaJ1 = new wxButton(Plateau,
                            ID_IAJ1,
                            wxString("IA Facile"),
                            wxPoint(25, 475),
                            wxSize(100, 50));
    
    ia2J1 = new wxButton(Plateau,
                            ID_IA2J1,
                            wxString("IA Moyen"),
                            wxPoint(25, 525),
                            wxSize(100, 50));
    
    ia3J1 = new wxButton(Plateau,
                            ID_IA3J1,
                            wxString("IA Difficile"),
                            wxPoint(25, 575),
                            wxSize(100, 50));

    userJ2 = new wxButton(Plateau,
                            ID_USERJ2,
                            wxString("Humain"),
                            wxPoint(775, 425),
                            wxSize(100, 50));
    userJ2->SetBackgroundColour(wxColour(* wxRED));

    iaJ2 = new wxButton(Plateau,
                            ID_IAJ2,
                            wxString("IA Facile"),
                            wxPoint(775, 475),
                            wxSize(100, 50));
    
    ia2J2 = new wxButton(Plateau,
                            ID_IA2J2,
                            wxString("IA Moyen"),
                            wxPoint(775, 525),
                            wxSize(100, 50));
    ia3J2 = new wxButton(Plateau,
                            ID_IA3J2,
                            wxString("IA Difficile"),
                            wxPoint(775, 575),
                            wxSize(100, 50));

    timer = new wxTimer(this,TIMER);

    
    int intervalle = 200;
    #ifdef SPEED 
    intervalle = SPEED;
    #endif
    timer->Start(intervalle);

    // Initialisation du plateau
    for (int i = 0; i < n; i++) {
        for(int k = 0; k < n; k++) {
            grid->SetRowSize(i, 600/n);
            grid->SetColSize(k, 600/n);
            if (j.g.getEtat(i,k) == Vide)
                if((i+k)%2 == 0)
                    grid->SetCellBackgroundColour(i,k,wxColour(0, 134, 65));
                else
                    grid->SetCellBackgroundColour(i,k,wxColour(0, 99, 45));
            else if (j.g.getEtat(i,k) == Noir)
                grid->SetCellBackgroundColour(i,k,wxColour(* wxBLACK));
            else if (j.g.getEtat(i,k) == Blanc)
                grid->SetCellBackgroundColour(i,k,wxColour(* wxWHITE));
            else
                grid->SetCellValue(i, k, "Erreur");
        }
     
    }
    
}

BEGIN_EVENT_TABLE(Fenetre, wxFrame)
    EVT_MENU(wxID_EXIT, Fenetre::OnQuit)
    EVT_GRID_CELL_LEFT_CLICK(Fenetre::OnLeftClick)
    EVT_BUTTON(ID_NvllPartie, Fenetre::OnNewGame)
    EVT_TIMER(TIMER, Fenetre::OnTimer)
    EVT_BUTTON(ID_USERJ1, Fenetre::OnUserJ1)
    EVT_BUTTON(ID_IAJ1, Fenetre::OnIAJ1)
    EVT_BUTTON(ID_IA2J1, Fenetre::OnIA2J1)
    EVT_BUTTON(ID_USERJ2, Fenetre::OnUserJ2)
    EVT_BUTTON(ID_IAJ2, Fenetre::OnIAJ2)
    EVT_BUTTON(ID_IA2J2, Fenetre::OnIA2J2)
    EVT_BUTTON(ID_IA3J1, Fenetre::OnIA3J1)
    EVT_BUTTON(ID_IA3J2, Fenetre::OnIA3J2)
END_EVENT_TABLE()


// q: Comment fermer la fenetre menu

void Fenetre::OnQuit(wxCommandEvent& event) {
    Close(true);
}
// #### Gestion des boutons de choix de l'IA ####
void Fenetre::OnUserJ1(wxCommandEvent& event) {
    flagJ1 = 0;
    iaJ1->SetBackgroundColour(wxColour(* wxWHITE));
    ia2J1->SetBackgroundColour(wxColour(* wxWHITE));
    userJ1->SetBackgroundColour(wxColour(* wxRED));
    ia3J1->SetBackgroundColour(wxColour(* wxWHITE));
}
void Fenetre::OnIAJ1(wxCommandEvent& event) {
    flagJ1 = 1;
    iaJ1->SetBackgroundColour(wxColour(* wxRED));
    ia2J1->SetBackgroundColour(wxColour(* wxWHITE));
    userJ1->SetBackgroundColour(wxColour(* wxWHITE));
    ia3J1->SetBackgroundColour(wxColour(* wxWHITE));
}
void Fenetre::OnIA2J1(wxCommandEvent& event){
    flagJ1 = 2;
    iaJ1->SetBackgroundColour(wxColour(* wxWHITE));
    ia2J1->SetBackgroundColour(wxColour(* wxRED));
    userJ1->SetBackgroundColour(wxColour(* wxWHITE));
    ia3J1->SetBackgroundColour(wxColour(* wxWHITE));
}
void Fenetre::OnIA3J1(wxCommandEvent& event){
    flagJ1 = 3;
    iaJ1->SetBackgroundColour(wxColour(* wxWHITE));
    ia2J1->SetBackgroundColour(wxColour(* wxWHITE));
    ia3J1->SetBackgroundColour(wxColour(* wxRED));
    userJ1->SetBackgroundColour(wxColour(* wxWHITE));
}

void Fenetre::OnUserJ2(wxCommandEvent& event) {
    flagJ2 = 0;
    iaJ2->SetBackgroundColour(wxColour(* wxWHITE));
    ia2J2->SetBackgroundColour(wxColour(* wxWHITE));
    userJ2->SetBackgroundColour(wxColour(* wxRED));
    ia3J2->SetBackgroundColour(wxColour(* wxWHITE));
}
void Fenetre::OnIAJ2(wxCommandEvent& event) {
    flagJ2 = 1;
    iaJ2->SetBackgroundColour(wxColour(* wxRED));
    ia2J2->SetBackgroundColour(wxColour(* wxWHITE));
    userJ2->SetBackgroundColour(wxColour(* wxWHITE));
    ia3J2->SetBackgroundColour(wxColour(* wxWHITE));

}
void Fenetre::OnIA2J2(wxCommandEvent& event){
    flagJ2 = 2;
    iaJ2->SetBackgroundColour(wxColour(* wxWHITE));
    ia2J2->SetBackgroundColour(wxColour(* wxRED));
    userJ2->SetBackgroundColour(wxColour(* wxWHITE));
    ia3J2->SetBackgroundColour(wxColour(* wxWHITE));
}
void Fenetre::OnIA3J2(wxCommandEvent& event){
    flagJ2 = 3;
    iaJ2->SetBackgroundColour(wxColour(* wxWHITE));
    ia2J2->SetBackgroundColour(wxColour(* wxWHITE));
    ia3J2->SetBackgroundColour(wxColour(* wxRED));
    userJ2->SetBackgroundColour(wxColour(* wxWHITE));
}
//################################################

void Fenetre::ChangeScore(){
    vector<int> Score = j.g.getScore();
    textJ1->SetLabel(wxString::Format(wxT("Score J1 :\n   %d"), Score[1]));
    textJ2->SetLabel(wxString::Format(wxT("Score J2 :\n   %d"), Score[0]));
}

void Fenetre::OnNewGame(wxCommandEvent& event){
    j = Jeu();
    int n = j.g.n;
    Fenetre::OnUserJ1(event);Fenetre::OnUserJ2(event);
    for (int i = 0; i < n; i++) {
        for(int k = 0; k < n; k++) {
            if (j.g.getEtat(i,k) == Vide)
                if((i+k)%2 == 0)
                    grid->SetCellBackgroundColour(i,k,wxColour(0, 134, 65));
                else
                    grid->SetCellBackgroundColour(i,k,wxColour(0, 99, 45));
            else if (j.g.getEtat(i,k) == Noir)
                grid->SetCellBackgroundColour(i,k,wxColour(* wxBLACK));
            else if (j.g.getEtat(i,k) == Blanc)
                grid->SetCellBackgroundColour(i,k,wxColour(* wxWHITE));
            else
                grid->SetCellValue(i, k, "Erreur");
        }
    }
    text->SetLabel(wxString("Au tour de J2 (Noir)"));
    ChangeScore();
    grid->ForceRefresh();
}


// Gestion du jeu par un humain
void Fenetre::OnLeftClick(wxGridEvent& event){
        int ligne = event.GetRow();
        int colonne = event.GetCol();
        grid->ClearSelection();
        
        if (j.est_valide(ligne, colonne, j.getJoueur())){
            
            if (j.getJoueur() == J1){
                j.jouerBlanc(ligne, colonne);
            }
            else
            {
                j.jouerNoir(ligne, colonne);
            }
            
            for (int i = 0; i < 8; i++) {
                for(int k = 0; k < 8; k++) {
                    if (j.g.getEtat(i,k) == Vide)
                        if((i+k)%2 == 0)
                            grid->SetCellBackgroundColour(i,k,wxColour(0, 134, 65));
                        else
                            grid->SetCellBackgroundColour(i,k,wxColour(0, 99, 45));
                    else if (j.g.getEtat(i,k) == Noir)
                        grid->SetCellBackgroundColour(i,k,wxColour(* wxBLACK));
                    else if (j.g.getEtat(i,k) == Blanc)
                        grid->SetCellBackgroundColour(i,k,wxColour(* wxWHITE));
                    else
                        grid->SetCellValue(i, k, "Erreur");
                }
            }
            grid->ForceRefresh();
            ChangeScore();
            /*Si le coup est valide
            On joue le coup
            On vérifie que le joueur suivant peut jouer
            Si oui 
                On lui passe la main
            Si non on redonne la main au joueur
            Si aucun des deux peut fin de partie*/

            if(j.getJoueur()==J1){
                if(j.peut_jouer(J2)){
                    j.setJoueur(J2);
                    text->SetLabel(wxString("Au tour de J2 (Noir)"));
                }
                else if(j.peut_jouer(J1)){
                    j.setJoueur(J1);
                    text->SetLabel(wxString("Au tour de J1 (Blanc) car J2 ne peut pas jouer"));
                }
                else{
                    vector<int> Score = j.g.getScore();
                    if(Score[1] > Score[0])
                        wxMessageBox("Fin de partie, J1 (Blanc) remporte la partie", "Fin", wxOK | wxICON_ERROR);
                    else if(Score[1] < Score[0])
                        wxMessageBox("Fin de partie, J2 (Noir) remporte la partie", "Fin", wxOK | wxICON_ERROR);
                    else
                        wxMessageBox("Fin de partie, ex-aequo", "Fin", wxOK | wxICON_ERROR);
                }
                    
                
            }
            else{
                if(j.peut_jouer(J1)){
                    j.setJoueur(J1);
                    text->SetLabel(wxString("Au tour de J1 (Blanc)"));
                }
                else if(j.peut_jouer(J1)){
                    j.setJoueur(J2);
                    text->SetLabel(wxString("Au tour de J2 (Noir) car J1 ne peut pas jouer"));
                }
                else{
                    vector<int> Score = j.g.getScore();
                    if(Score[0] > Score[1])
                        wxMessageBox("Fin de partie, J1 (Blanc) remporte la partie", "Fin", wxOK | wxICON_ERROR);
                    else if(Score[0] < Score[1])
                        wxMessageBox("Fin de partie, J2 (Noir) remporte la partie", "Fin", wxOK | wxICON_ERROR);
                    else
                    wxMessageBox("Fin de partie, ex-aequo", "Fin", wxOK | wxICON_ERROR);
                }
                    
                
            }
        }
        else
        {
            wxMessageBox("Coup invalide", "Erreur", wxOK | wxICON_ERROR);
        }
            
}

// Fonction pour choisir un coup aléatoire
Coordonnees Fenetre::coup_random(Joueur J){
    vector<Coordonnees> res;
    int ligne;
    int colonne;
    int r;
    int n = j.g.n;
    for (int i=0; i<n; i++){
        for (int k=0; k<n; k++){
            if (j.g.getEtat(i,k) == Vide){
                if (j.est_valide(i,k,J)){
                    colonne = k;
                    ligne = i;

                    res.push_back(Coordonnees(ligne, colonne));
                }
            } 
        }
    }
    if (res.size() == 0){
        return Coordonnees(-1,-1); // On renvoie une coordonnée invalide si aucun coup n'est possible
    }
    else{
        r = rand() % res.size();
        return res[r];
    }
}


// Fonction pour choisir un coup selon un algorithme glouton
Coordonnees Fenetre::coup_max(Joueur J){ //Glouton
    int n = j.g.n;
    int max = 0;
    int ligne;
    int colonne;
    int nb;
    for (int i=0; i<n; i++){
        for (int k=0; k<n; k++){
            if (j.g.getEtat(i,k) == Vide){
                if (j.est_valide(i,k,J)){
                    nb = j.nb_pions(i,k,J);
                    if (nb > max){
                        max = nb;
                        colonne = k;
                        ligne = i;
                    }
                }
            } 
        }
    }
    if (max == 0)
        return Coordonnees(-1,-1); // On renvoie une coordonnée invalide si aucun coup n'est possible
    
    else
        return Coordonnees(ligne, colonne);
}


//#################### MINMAX ####################

// Fonction pour choisir un coup selon un algorithme minimax
// Cet algorithme est récursif et cherche à maximiser le score du joueur J en minimisant celui de l'adversaire
// On veut donc calculer tous les coups possibles de J et calculer toutes les réponses de l'adversaire
// On choisit le coup qui maximise le score de J
// Joriginal est le joueur qui doit poser le coup
// Jactu est le joueur pour lequel on vérifie les coups possibles
int Fenetre::min_max_val(Joueur Jactu,Joueur Joriginal,int profondeur){
    if(profondeur==4){
        if(Jactu==Joriginal){
            return j.g.getScore()[0]-j.g.getScore()[1];
        }
        else{
            return j.g.getScore()[1]-j.g.getScore()[0];
        }
    }
    // On récupère la liste des coups possibles pour Jactu
    vector<Coordonnees> res;
    int ligne;
    int colonne;
    int n = j.g.n;
    for (int i=0; i<n; i++){
        for (int k=0; k<n; k++){
            if (j.g.getEtat(i,k) == Vide){
                if (j.est_valide(i,k,Jactu)){
                    colonne = k;
                    ligne = i;
                    res.push_back(Coordonnees(ligne, colonne));
                }
            } 
        }
    }

    if(res.size()==0){
        return min_max_val(Jactu==J1?J2:J1,Joriginal,profondeur+1);
    }
    else{
        int meilleurCoupScore = -999; // On cherche le maximum
        if (Jactu!=Joriginal){
            meilleurCoupScore = 999; // On cherche le minimum
        }
        // On teste tous les coups possibles
        for(long unsigned int i =0; i<res.size();i++){
            // On fait une copie du jeu
            Jeu j2 = j;
            // On joue le coup
            if(Jactu==J1)
                j2.jouerBlanc(res[i].getx(),res[i].gety());
            else
                j2.jouerNoir(res[i].getx(),res[i].gety());
            
            int valeur = min_max_val(Jactu==J1?J2:J1,Joriginal,profondeur+1);
            if (Jactu==Joriginal){
                if(valeur>meilleurCoupScore){
                    meilleurCoupScore = valeur;
                }
            }
            else{
                if(valeur<meilleurCoupScore){
                    meilleurCoupScore = valeur;
                }
            }

        }
        return meilleurCoupScore;

    }
}


Coordonnees Fenetre::min_max(Joueur Jactu,Joueur Joriginal,int profondeur){
    // On récupère la liste des coups possibles pour Jactu
    vector<Coordonnees> res;
    int ligne;
    int colonne;
    int n = j.g.n;
    for (int i=0; i<n; i++){
        for (int k=0; k<n; k++){
            if (j.g.getEtat(i,k) == Vide){
                if (j.est_valide(i,k,Jactu)){
                    colonne = k;
                    ligne = i;
                    res.push_back(Coordonnees(ligne, colonne));
                }
            } 
        }
    }

    if(res.size()==0){
        return Coordonnees(-1,-1);
    }
    else{
        int meilleurCoupScore = -999; // On cherche le maximum
        if (Jactu!=Joriginal){
            meilleurCoupScore = 999; // On cherche le minimum
        }
        // On teste tous les coups possibles
        
        for(long unsigned int i =0; i<res.size();i++){
            // On fait une copie du jeu
            Jeu j2 = j;
            // On joue le coup
            if(Jactu==J1)
                j2.jouerBlanc(res[i].getx(),res[i].gety());
            else
                j2.jouerNoir(res[i].getx(),res[i].gety());
            
            int valeur = min_max_val(Jactu==J1?J2:J1,Joriginal,profondeur+1);
            if (Jactu==Joriginal){
                if(valeur>meilleurCoupScore){
                    meilleurCoupScore = valeur;
                    ligne = res[i].getx();
                    colonne = res[i].gety();
                }
            }
            else{
                if(valeur<meilleurCoupScore){
                    meilleurCoupScore = valeur;
                    ligne = res[i].getx();
                    colonne = res[i].gety();
                }
            }
        }
        return Coordonnees(ligne,colonne);
    }
}

//#################### FIN MINMAX ####################


void Fenetre::OnTimer(wxTimerEvent& event){
    int n = j.g.n;
    //Gestion du bot blanc
    if (flagJ1!=0 && j.getJoueur()==J1){
        // On joue contre l'IA
        // On récupère le coup de l'IA
        int colonne;
        int ligne;
        Coordonnees c(-1,-1);
        if(flagJ1==1)
            c = coup_random(J1);
        else if(flagJ1==2)
            c = coup_max(J1);
        else if(flagJ1==3)
            c = min_max(J1,J1,0);
        ligne = c.getx();
        colonne = c.gety();

        if(ligne!=-1 && colonne !=-1){
                // On joue le coup
            cout << "IA blanche JOUE en " << ligne << " " << colonne << endl;
            j.jouerBlanc(ligne, colonne);
            // On rafraichit l'affichage
            
            // On vérifie que le joueur suivant peut jouer
            // Si oui 
            //      On lui passe la main
            // Si non on redonne la main au joueur
            // Si aucun des deux peut fin de partie
            if(j.peut_jouer(J2)){
                        j.setJoueur(J2);
                        text->SetLabel(wxString("Au tour de J2 (Noir)"));
                    }
                    else if(j.peut_jouer(J1)){
                        j.setJoueur(J1);
                        text->SetLabel(wxString("Au tour de J1 (Blanc) car J2 ne peut pas jouer"));
                    }
                    else
                        cout << "Fin de partie" << endl;
        }
        else{
            vector<int> Score = j.g.getScore();
            if(Score[1] > Score[0])
                wxMessageBox("Fin de partie, J1 (Blanc) remporte la partie", "Fin", wxOK | wxICON_ERROR);
            else if(Score[1] < Score[0])
                wxMessageBox("Fin de partie, J2 (Noir) remporte la partie", "Fin", wxOK | wxICON_ERROR);
            else
                wxMessageBox("Fin de partie, ex-aequo", "Fin", wxOK | wxICON_ERROR);
            flagJ1 = 0;
            iaJ1->SetBackgroundColour(wxColour(* wxWHITE));
            ia2J1->SetBackgroundColour(wxColour(* wxWHITE));
            userJ1->SetBackgroundColour(wxColour(* wxRED));
            ia3J1->SetBackgroundColour(wxColour(* wxWHITE));
            flagJ2 = 0;
            iaJ2->SetBackgroundColour(wxColour(* wxWHITE));
            ia2J2->SetBackgroundColour(wxColour(* wxWHITE));
            userJ2->SetBackgroundColour(wxColour(* wxRED));
            ia3J2->SetBackgroundColour(wxColour(* wxWHITE));
        }
    }
        
    //Gestion du bot noir
    else if (flagJ2!=0 && j.getJoueur()==J2){
        // On joue contre l'IA
        // On récupère le coup de l'IA
        int colonne;
        int ligne;
        Coordonnees c(-1,-1);
        if(flagJ2==1)
            c = coup_random(J2);
        else if(flagJ2==2)
            c = coup_max(J2);
        else if(flagJ2==3)
            c = min_max(J2,J2,0);
        ligne = c.getx();
        colonne = c.gety();
        if(ligne!=-1 && colonne !=-1){
                // On joue le coup
            cout << "IA Noire JOUE en " << ligne << " " << colonne << endl;
            j.jouerNoir(ligne, colonne);
            // On rafraichit l'affichage
            
            // On vérifie que le joueur suivant peut jouer
            // Si oui 
            //      On lui passe la main
            // Si non on redonne la main au joueur
            // Si aucun des deux peut fin de partie
            if(j.peut_jouer(J1)){
                        j.setJoueur(J1);
                        text->SetLabel(wxString("Au tour de J1 (Blanc)"));
                    }
                    else if(j.peut_jouer(J2)){
                        j.setJoueur(J2);
                        text->SetLabel(wxString("Au tour de J2 (Noir) car J1 ne peut pas jouer"));
                    }
                    else
                        
                        cout << "Fin de partie" << endl;
        }
        else{
            vector<int> Score = j.g.getScore();
            if(Score[1] > Score[0])
                wxMessageBox("Fin de partie, J1 (Blanc) remporte la partie", "Fin", wxOK | wxICON_ERROR);
            else if(Score[1] < Score[0])
                wxMessageBox("Fin de partie, J2 (Noir) remporte la partie", "Fin", wxOK | wxICON_ERROR);
            else
                wxMessageBox("Fin de partie, ex-aequo", "Fin", wxOK | wxICON_ERROR);
            flagJ1 = 0;
            iaJ1->SetBackgroundColour(wxColour(* wxWHITE));
            ia2J1->SetBackgroundColour(wxColour(* wxWHITE));
            userJ1->SetBackgroundColour(wxColour(* wxRED));
            ia3J1->SetBackgroundColour(wxColour(* wxWHITE));

            flagJ2 = 0;
            iaJ2->SetBackgroundColour(wxColour(* wxWHITE));
            ia2J2->SetBackgroundColour(wxColour(* wxWHITE));
            userJ2->SetBackgroundColour(wxColour(* wxRED));
            ia3J2->SetBackgroundColour(wxColour(* wxWHITE));
        }
        
    }
    else{
        // On joue contre un autre joueur
        // On ne fait rien
    }
    
    for (int i = 0; i < n; i++) {
                    for(int k = 0; k < n; k++) {
                        if (j.g.getEtat(i,k) == Vide)
                            if((i+k)%2 == 0)
                                grid->SetCellBackgroundColour(i,k,wxColour(0, 134, 65));
                            else
                                grid->SetCellBackgroundColour(i,k,wxColour(0, 99, 45));
                        else if (j.g.getEtat(i,k) == Noir)
                            grid->SetCellBackgroundColour(i,k,wxColour(* wxBLACK));
                        else if (j.g.getEtat(i,k) == Blanc)
                            grid->SetCellBackgroundColour(i,k,wxColour(* wxWHITE));
                        else
                            grid->SetCellValue(i, k, "Erreur");
                    }
                }
                grid->ForceRefresh();
                ChangeScore();
}