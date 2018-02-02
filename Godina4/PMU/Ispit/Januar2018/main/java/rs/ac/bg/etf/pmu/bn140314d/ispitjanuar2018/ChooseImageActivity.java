package rs.ac.bg.etf.pmu.bn140314d.ispitjanuar2018;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.widget.GridView;

import java.util.ArrayList;

public class ChooseImageActivity extends AppCompatActivity {

    private ArrayList<Integer> imageIds = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_choose_image);

        loadImages();
    }

    private void loadImages() {
        GridView gridView = findViewById(R.id.grid);

        final ImageGridAdapter adapter = new ImageGridAdapter(this, getImages());
        gridView.setAdapter(adapter);

        final Activity activity = this;

        gridView.setOnItemClickListener((adapterView, view, position, id) -> {
            Intent intent = new Intent(activity, DrawActivity.class);
            intent.putExtra("ID", imageIds.get(position));
            startActivity(intent);
        });
    }

    private Uri[] getImages() {
        imageIds.clear();

        String[] projection = {MediaStore.Images.Media._ID};
        Uri uri = MediaStore.Images.Media.EXTERNAL_CONTENT_URI;

        Cursor cursor = MediaStore.Images.Media.query(getContentResolver(), uri, projection);

        if (cursor == null) {
            return new Uri[0];
        }

        final int MAX_SIZE = 10;

        int size = cursor.getCount();
        if (size > MAX_SIZE) size = MAX_SIZE;

        Uri[] imageUris = new Uri[size];

        cursor.moveToFirst();
        for (int i = 0; i < size; i++) {
            cursor.moveToPosition(i);
            int columnIndex = cursor.getColumnIndexOrThrow(MediaStore.Images.Media._ID);
            int imageId = cursor.getInt(columnIndex);
            Uri imageUri = Uri.withAppendedPath(uri, imageId + "");
            imageUris[i] = imageUri;
            imageIds.add(imageId);
        }

        cursor.close();

        return imageUris;
    }
}
