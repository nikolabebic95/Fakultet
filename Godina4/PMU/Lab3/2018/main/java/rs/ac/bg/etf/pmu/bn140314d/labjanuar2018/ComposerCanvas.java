package rs.ac.bg.etf.pmu.bn140314d.labjanuar2018;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.view.View;

import java.util.ArrayList;

import static android.view.MotionEvent.ACTION_DOWN;
import static android.view.MotionEvent.ACTION_MOVE;
import static android.view.MotionEvent.ACTION_UP;

public class ComposerCanvas extends View {
    private ArrayList<Bitmap> bitmaps = new ArrayList<>();

    private int oldW = 0;
    private int oldH = 0;

    public ComposerCanvas(Context context) {
        super(context);
    }

    public ComposerCanvas(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public ComposerCanvas(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
    }

    {
        Bitmap bitmap;
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_1);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_2);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_3);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_4);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_5);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_6);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_7);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_8);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_9);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_10);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_11);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_12);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_13);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_14);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_15);
        bitmaps.add(bitmap);
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pic_16);
        bitmaps.add(bitmap);

        setOnTouchListener((view, motionEvent) -> {
            view.performClick();
            float x = motionEvent.getX();
            float y = motionEvent.getY();
            
            switch (motionEvent.getAction()) {
                case ACTION_DOWN:
                    Model.down(x, y);
                    break;
                case ACTION_MOVE:
                    Model.move(x, y);
                    break;
                case ACTION_UP:
                    Model.up(x, y);
                    break;
            }

            ComposerCanvas.this.invalidate();
            return true;
        });
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        int w = getWidth();
        int h = getHeight();
        drawUpperBitmaps(canvas, w, h);
        Model.draw(canvas, bitmaps);
    }

    private void drawUpperBitmaps(Canvas canvas, int w, int h) {
        float realW = w / 8.0F;
        float realH = h / 4.0F;
        Model.setWH(realW, realH);

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                int k = i * 8 + j;
                Bitmap bitmap = bitmaps.get(k);
                if (w != oldW || h != oldH) {
                    Bitmap resized = Bitmap.createScaledBitmap(bitmap, (int)realW, (int)realH, false);
                    bitmaps.remove(k);
                    bitmaps.add(k, resized);
                    bitmap.recycle();
                    bitmap = resized;
                }

                canvas.drawBitmap(bitmap, realW * j, realH * i, null);
            }
        }

        oldH = h;
        oldW = w;
    }
}
