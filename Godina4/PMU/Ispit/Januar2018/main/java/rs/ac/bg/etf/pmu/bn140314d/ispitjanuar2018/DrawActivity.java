package rs.ac.bg.etf.pmu.bn140314d.ispitjanuar2018;

import android.content.Context;
import android.content.Intent;
import android.hardware.SensorManager;
import android.net.Uri;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ImageView;

public class DrawActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_draw);

        Intent intent = getIntent();

        int imageId = intent.getIntExtra("ID", 0);

        Uri uri = MediaStore.Images.Media.EXTERNAL_CONTENT_URI;
        Uri imageUri = Uri.withAppendedPath(uri, imageId + "");

        ImageView imageView = findViewById(R.id.bigImage);

        imageView.setImageURI(imageUri);

        CanvasView canvasView = findViewById(R.id.canvasView);
        canvasView.initSensors((SensorManager)getSystemService(Context.SENSOR_SERVICE));
    }
}
