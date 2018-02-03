package rs.ac.bg.etf.pmu.bn140314d.labjanuar2018;

import android.media.MediaPlayer;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private ArrayList<MediaPlayer> mediaPlayers = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public synchronized void playMusic(View view) {
        stopMusic(view);
        mediaPlayers = Model.getComposition(this);
        if (!mediaPlayers.isEmpty()) mediaPlayers.get(0).start();
    }

    public synchronized void stopMusic(View view) {
        mediaPlayers.forEach(MediaPlayer::stop);
        mediaPlayers.clear();
    }
}
