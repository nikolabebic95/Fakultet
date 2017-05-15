/*Klasa GeoRegion, ciji je interfejs dat u nastavku, apstrahuje geografski region i implementirana
je u potpunosti.Objekti ove klase zauzimaju mnogo prostora u memoriji, pa se mogu ucitavati po potrebi, 
dinamicki.Ovo ucitavanje obavlja staticka operacija GeoRegion::load, pri cemu se objekat identifikuje 
datim nazivom geografskog regiona(niz znakova).Ostale operacije ove klase vracaju vrednosti 
nekih svojstava geografskog regiona.
Potrebno je u potpunosti implementirati klasu GeoRegionProxy ciji je intefejs dat u nastavku. 
Objekti ove klase sluze kao posrednici(proxy) do objekata klase GeoRegion, pri cemu pruzaju isti 
interfejs kao i „originali“, s tim da skrivaju detalje implementacije i tehniku dinamickog ucitavanja 
od svojih korisnika.Korisnici klase GeoRegionProxy vide njene objekte na sasvim uobicajen nacin, 
mogu ih kreirati datim konstruktorom i pozivati date operacije interfejsa, ne znajuci da odgovarajuca 
struktura podataka mozda nije ucitana u memoriju.
class GeoRegion {
public:
	static GeoRegion* load(char* regionName);
	double getSurface();
	double getHighestPeak();
};
class GeoRegionProxy {
public:
	GeoRegionProxy(char* regionName);
	double getSurface();
	double getHighestPeak();
};*/


class GeoRegionProxy{
public:
    GeoRegionProxy(char* regionName):region_name_(regionName){}    
    double getSurface(){
        ensureLoad();
        return geo_region_.getSurface();
    }
    double getHighestPeak(){
        ensureLoad();
        return geo_region_.getHighestPeak();
    }
private:
    char *region_name_;
    GeoRegion* geo_region_;
    bool loaded_=false;
    void ensureLoad(){
        if(!loaded_){
            geo_region_=GeoRegion::load(region_name_);
            loaded_=true;
        }
    }
};
