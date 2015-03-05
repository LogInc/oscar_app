package com.log.oscar;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import android.app.Activity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class Modes extends Activity {
	
	int socketPort = 8888;
	String ipAddress = "192.168.1.1";
	byte State;
	Button power,study,lights,gather;
	TextView state;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_modes);
		
		
		power = (Button)findViewById(R.id.powerSavings);
		study = (Button)findViewById(R.id.Study);
		lights = (Button)findViewById(R.id.lightsOut);
		gather = (Button)findViewById(R.id.gMode);
		state = (TextView) findViewById(R.id.state);
		
		
		power.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				State = 'P';
				state.setText("Power Saving");
				MyClientTask myClientTask = new MyClientTask(ipAddress,
						socketPort, State);
				myClientTask.execute();
			}
		});
		
		study.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				State = 'S';
				state.setText("Study Mode");
				MyClientTask myClientTask = new MyClientTask(ipAddress,
						socketPort, State);
				myClientTask.execute();
			}
		});
		
		lights.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				State = 'L';
				state.setText("Lights Out");
				MyClientTask myClientTask = new MyClientTask(ipAddress,
						socketPort, State);
				myClientTask.execute();
			}
		});
		
		gather.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				State = 'G';
				state.setText("Gathering Mode");
				MyClientTask myClientTask = new MyClientTask(ipAddress,
						socketPort, State);
				myClientTask.execute();
			}
		});
		
		
	}
	
	public class MyClientTask extends AsyncTask<Void, Void, Void> {

		String dstAddress;
		int dstPort;
		//String msgToServer;
		byte msgToServer;
		byte response;
		
		MyClientTask(String addr, int port, byte msg) {
			dstAddress = addr;
			dstPort = port;
			msgToServer = msg;
		}

		@Override
		protected Void doInBackground(Void... params) {
			// TODO Auto-generated method stub

			Socket socket = null;
			DataOutputStream dOut = null;
			DataInputStream dIn = null;

			try {
				socket = new Socket(dstAddress, dstPort);
				dIn = new DataInputStream(socket.getInputStream());
				dOut = new DataOutputStream(socket.getOutputStream());

				dOut.writeByte(msgToServer);

				//dOut.writeUTF(msgToServer);
				
				response = dIn.readByte();

			} catch (UnknownHostException e) {
				e.printStackTrace();

			} catch (IOException e) {
				e.printStackTrace();

			} finally {
				if (socket != null) {
					try {
						socket.close();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}

				if (dOut != null) {
					try {
						dOut.close();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}

				if (dIn != null) {
					try {
						dIn.close();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}

			}

			return null;
		}

		@Override
		protected void onPostExecute(Void result) {
			// display.setText(response);
			super.onPostExecute(result);
		}

	}
}

