package rs.ac.bg.etf.pmu.bn140314d.labjanuar2018;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.media.MediaPlayer;

import java.util.ArrayList;

final class Model {
    private Model() {}

    private static ArrayList<Integer> composition = new ArrayList<>();

    private static int currentComposition = 0;
    private static float currentX = 0;
    private static float currentY = 0;

    private static float originalX = 0;
    private static float originalY = 0;

    private static float w;
    private static float h;

    private static long timestamp = 0;
    private static int removedIndex = 0;

    private static final float EPSILON = 50F;
    private static boolean shouldBeRemoved = true;

    private static final long THRESHOLD = 1000;

    static synchronized void setWH(float w, float h) {
        Model.w = w;
        Model.h = h;
    }

    static synchronized ArrayList<MediaPlayer> getComposition(Activity activity) {
        ArrayList<MediaPlayer> mediaPlayers = new ArrayList<>();

        for (Integer num : composition) {
            int resIndex = Model.getMediaIndex(num);
            MediaPlayer mediaPlayer = MediaPlayer.create(activity, resIndex);
            mediaPlayers.add(mediaPlayer);
        }

        for (int i = 0; i < mediaPlayers.size() - 1; i++) {
            mediaPlayers.get(i).setNextMediaPlayer(mediaPlayers.get(i + 1));
        }

        return mediaPlayers;
    }

    static synchronized void down(float x, float y) {
        int index = getCompositionIndex(x, y);
        if (index > 0) {
            currentComposition = index;
            currentX = x - w / 2;
            currentY = y - h / 2;
            timestamp = 0;
        } else {
            index = getArrayIndex(x, y);
            if (index >= composition.size()) return;

            currentComposition = composition.get(index);
            composition.remove(index);
            composition.add(index, 0);
            removedIndex = index;
            shouldBeRemoved = true;

            currentX = x - w / 2;
            currentY = y - h / 2;
            timestamp = System.currentTimeMillis();
            originalX = currentX;
            originalY = currentY;
        }
    }

    static synchronized void move(float x, float y) {
        if (currentComposition > 0) {
            currentX = x - w / 2;
            currentY = y - h / 2;
            if (timestamp != 0) {
                if (dist(currentX, currentY, originalX, originalY) > EPSILON) {
                    shouldBeRemoved = false;
                }
            }
        }
    }

    static synchronized void up(float x, float y) {
        move(x, y);
        if (currentComposition > 0) {
            if (y > h * 2 && timestamp == 0) composition.add(currentComposition);
            else if (timestamp != 0) {
                if (System.currentTimeMillis() - timestamp > THRESHOLD && shouldBeRemoved) {
                    composition.remove(removedIndex);
                } else {
                    composition.remove(removedIndex);
                    if (currentX - originalX > w && removedIndex != 7 && removedIndex != 15 && removedIndex != composition.size()) {
                        composition.add(removedIndex + 1, currentComposition);
                    } else if (originalX - currentX > w && removedIndex != 0 && removedIndex != 8) {
                        composition.add(removedIndex - 1, currentComposition);
                    } else {
                        composition.add(removedIndex, currentComposition);
                    }
                }
            }

            currentComposition = 0;
            currentX = 0;
            currentY = 0;
        }
    }

    static synchronized void draw(Canvas canvas, ArrayList<Bitmap> bitmaps) {
        for (int k = 0; k < composition.size(); k++) {
            float x = k * w;
            float y = 2 * h;
            if (k >= 8) {
                y += h;
                x -= 8 * w;
            }

            if (composition.get(k) == 0) continue;
            Bitmap bitmap = bitmaps.get(composition.get(k) - 1);
            canvas.drawBitmap(bitmap, x, y, null);
        }

        if (currentComposition > 0) {
            Bitmap bitmap = bitmaps.get(currentComposition - 1);
            canvas.drawBitmap(bitmap, currentX, currentY, null);
        }
    }

    private static int getCompositionIndex(float x, float y) {
        if (y > 2 * h) return 0;
        if (x > 8 * w) return 0;

        int xIndex = (int)(x / w);
        int yIndex = (int)(y / h);

        return xIndex + 8 * yIndex + 1;
    }

    private static int getArrayIndex(float x, float y) {
        if (y < 2 * h) return 0;
        if (x > 8 * w) return 0;

        int xIndex = (int)(x / w);
        int yIndex = (int)(y / h);

        return xIndex + 8 * yIndex - 16;
    }

    private static float dist(float x1, float y1, float x2, float y2) {
        float x = x1 - x2;
        float y = y1 - y2;
        return (float)Math.sqrt(x * x + y * y);
    }

    private static int getMediaIndex(int i) {
        switch (i) {
            case 1:
                return R.raw.sound_1;
            case 2:
                return R.raw.sound_2;
            case 3:
                return R.raw.sound_3;
            case 4:
                return R.raw.sound_4;
            case 5:
                return R.raw.sound_5;
            case 6:
                return R.raw.sound_6;
            case 7:
                return R.raw.sound_7;
            case 8:
                return R.raw.sound_8;
            case 9:
                return R.raw.sound_8;
            case 10:
                return R.raw.sound_10;
            case 11:
                return R.raw.sound_11;
            case 12:
                return R.raw.sound_12;
            case 13:
                return R.raw.sound_13;
            case 14:
                return R.raw.sound_14;
            case 15:
                return R.raw.sound_15;
            case 16:
                return R.raw.sound_16;
        }

        return 0;
    }
}
