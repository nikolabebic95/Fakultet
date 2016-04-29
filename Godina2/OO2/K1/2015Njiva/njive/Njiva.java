package njive;

/**
 * Њива је парцела која има задат годишњи принос по квадратном метру. Принос по
 * квадратном метру може да се промени. Ознака врсте је N. Текстуални облик је
 * парцела:приносПоМ.
 */
public class Njiva extends Parcela {
    private double godisnjiPrinos_;

    public Njiva(double povrsina, double godisnjiPrinos) {
        super(povrsina);
        godisnjiPrinos_ = godisnjiPrinos;
    }

    @Override
    public char vrsta() {
        return 'N';
    }

    @Override
    public double prinos(int godina) {
        return godisnjiPrinos_ * godina;
    }

    @Override
    public String toString() {
        return super.toString() + ":" + godisnjiPrinos_;
    }
}
