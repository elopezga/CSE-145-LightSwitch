package com.greenbits.lightswitch;

import android.os.AsyncTask;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

/**
 * Created by edgar on 5/1/16.
 */
public class ThingSpeakComm {

    private String THINGSPEAK_CHANNEL_URL = "https://api.thingspeak.com/channels/";
    private String THINGSPEAK_CHANNEL_ID = "111722";
    private String THINGSPEAK_API_KEY_STRING = "api_key=";
    private String THINGSPEAK_API_KEY_GET = "SE5ZR5HILIB7FF4T";
    private String THINGSPEAK_API_KEY_POST = "ZKME42ICZ835MKTK";
    private String THINGSPEAK_LATEST = "/last.txt?";

    private String THINGSPEAK_UPDATE_URL = "https://api.thingspeak.com/update.json?";

    public StringBuilder extractResponse(HttpURLConnection httpsession) throws IOException{
        BufferedReader buffReader = new BufferedReader(new InputStreamReader(httpsession.getInputStream()));
        StringBuilder strBuilder = new StringBuilder();
        String line;

        while( (line = buffReader.readLine()) != null){
            strBuilder.append(line).append("\n");
        }
        buffReader.close();
        return strBuilder;
    }

    public String getLightStatus(String lightnum){
        String url_str = THINGSPEAK_CHANNEL_URL+THINGSPEAK_CHANNEL_ID+"/fields/"+lightnum+THINGSPEAK_LATEST
                +THINGSPEAK_API_KEY_STRING+THINGSPEAK_API_KEY_GET;
        String response = "-1"; // Default thingspeak access denied
        HttpURLConnection urlConnection = null;
        try {
            URL url = new URL(url_str);
            urlConnection = (HttpURLConnection) url.openConnection();
            response = extractResponse(urlConnection).toString();
        } catch(MalformedURLException u){
            u.printStackTrace();
        } catch(IOException i){
            i.printStackTrace();
        } finally {
            urlConnection.disconnect();
        }

        return response;

    }

    public String setLightStatus(String lightnum, String status){
        String url_str = THINGSPEAK_UPDATE_URL+THINGSPEAK_API_KEY_STRING+THINGSPEAK_API_KEY_POST+"&"
                +"field"+lightnum+"="+status;
        String response = "-1";
        Log.d("LightSwitch", url_str);
        HttpURLConnection urlConnection = null;
        try{
            URL url = new URL(url_str);
            urlConnection = (HttpURLConnection) url.openConnection();
            //Log.d("LightSwitch", extractResponse(urlConnection).toString());
            response = extractResponse(urlConnection).toString();
            Log.d("LightSwitch", response);
        } catch(MalformedURLException u){
            u.printStackTrace();
        } catch(IOException i){
            i.printStackTrace();
        }finally {
            urlConnection.disconnect();
        }

        return response;
    }

}
