package com.greenbits.lightswitch;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.TextView;

public class ControlActivity extends AppCompatActivity {
    private static String light1Status;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_control);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

       FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });

        final Button toggleButton = (Button) findViewById(R.id.button_update);
        final TextView lightstatustext = (TextView) findViewById(R.id.textView_light);
        findViewById(R.id.progressBar).setVisibility(View.GONE);

        toggleButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        ThingSpeakComm tpcom = new ThingSpeakComm();
                        String response;
                        //Log.d("LightSwitch", "Status: " + light1Status);
                        //Log.d("LightSwitch", Boolean.toString(light1Status.equals("0")));
                        if( light1Status.equals("0") ){
                            do {
                                response = tpcom.setLightStatus("1", "1").replace("\n", "");

                                runOnUiThread(new Runnable() {
                                    @Override
                                    public void run() {
                                        findViewById(R.id.progressBar).setVisibility(View.VISIBLE);
                                    }
                                });

                            } while( response.equals("0"));
                        }else {
                            do {
                                response = tpcom.setLightStatus("1", "0").replace("\n", "");

                                runOnUiThread(new Runnable() {
                                    @Override
                                    public void run() {
                                        findViewById(R.id.progressBar).setVisibility(View.VISIBLE);
                                    }
                                });

                            } while( response.equals("0"));
                        }

                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                findViewById(R.id.progressBar).setVisibility(View.GONE);
                            }
                        });
                        //Log.d("LightSwitch", Boolean.toString(response.equals("0")));
                    }
                }).start();
            }
        });


        /* Set up view updater */
        Thread updateViews = new Thread(){
            @Override
            public void run(){
                try{
                    while(!isInterrupted()){
                        ThingSpeakComm tpcom = new ThingSpeakComm();
                        light1Status = tpcom.getLightStatus("1").replace("\n", "");

                        Thread.sleep(1000);
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                lightstatustext.setText("Light status: " + light1Status);
                            }
                        });
                    }
                }catch (InterruptedException e){
                    e.printStackTrace();
                }
            }
        };
        updateViews.start();





    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_control, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
