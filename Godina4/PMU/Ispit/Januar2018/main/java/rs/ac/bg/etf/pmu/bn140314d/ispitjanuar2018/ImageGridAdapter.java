package rs.ac.bg.etf.pmu.bn140314d.ispitjanuar2018;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.graphics.Bitmap;
import android.net.Uri;
import android.provider.MediaStore;
import android.support.annotation.NonNull;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;

import java.io.IOException;

public class ImageGridAdapter extends ArrayAdapter<Uri> {

    private Uri[] imageUris;
    private Activity context;

    ImageGridAdapter(@NonNull Activity context, @NonNull Uri[] imageUris) {
        super(context, R.layout.grid_element, imageUris);

        this.context = context;
        this.imageUris = imageUris;
    }

    @SuppressLint("InflateParams")
    @Override
    public @NonNull View getView(int position, View convertView, @NonNull ViewGroup parent) {
        View rowView = convertView;
        if (rowView == null) {
            LayoutInflater inflater = context.getLayoutInflater();
            rowView = inflater.inflate(R.layout.grid_element, null, true);
        }

        ImageView imageView = rowView.findViewById(R.id.imageRow);

        try {
            Bitmap original = MediaStore.Images.Media.getBitmap(getContext().getContentResolver(), imageUris[position]);
            Bitmap bitmap = Bitmap.createScaledBitmap(original, 100, 100, false);
            original.recycle();
            imageView.setImageBitmap(bitmap);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return rowView;
    }
}
