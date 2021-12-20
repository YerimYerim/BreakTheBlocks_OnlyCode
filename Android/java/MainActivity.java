package com.example.Blocks;

import androidx.appcompat.app.AppCompatActivity;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.Layout;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.TextView;
import com.example.Blocks.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'Blocks' library on application startup.
    FrameLayout layout;
    GL3JNIView mView;
    TextView RoundTextView;
    SurfaceHolder surfaceHolder;
    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        setContentView(R.layout.activity_main);
        mView = new GL3JNIView(getApplication());
        layout = findViewById(R.id.Main);
        layout.addView(mView);
        RoundTextView = (TextView) findViewById(R.id.score);
        RoundTextView.setText(GL3JNILib.getRoundCount());
        new Thread(new Runnable()
        {
            @Override
            public void run()
            {
                while (!Thread.interrupted())
                    try
                    {
                        Thread.sleep(1000); //1초 간격으로 실행
                        runOnUiThread(new Runnable()
                        {
                            @Override
                            public void run()
                            {
                                RoundTextView.setText(GL3JNILib.getRoundCount());
                            }
                        });
                    }
                    catch (InterruptedException e)
                    {
                        // error
                    }
            }
        }).start();
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
    }
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        float x = event.getX();
        float y = event.getY();

        switch (event.getAction()) {

            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_MOVE:
                GL3JNILib.InputEvent(true, x, y);
                break;
            case MotionEvent.ACTION_UP:
                GL3JNILib.InputEvent(false, x, y);
                break;
            default:
                break;

        }

        return super.onTouchEvent(event);
    }
}