using UnityEngine;
using System.Collections;

using System.Xml;

/*
	created by pokpoongryu

	강의용으로 쓰기 위해 작성한 
	초간단 형태의 GET방식 웹통신모듈
*/
public class CRyuClient
{
	//응답데이터 처리 핸들러로 쓸 함수 표현형식 정의
	public delegate void RyuHandler(XmlDocument tXML);
	
	
	RyuHandler mHandler = null;	//delegate문법.
	public WWW mWWW = null;	




	private string mGameServerURL 	= "";
	private int mSequenceIndex 		= 0;


	protected string mCurURL 		= "";
	protected MonoBehaviour mpMone 	= null;




	//통신타입 
	const int TYPE_GET = 0;
	const int TYPE_POST = 1;

	protected int mTypeTransmit = 0;





	//data
	public string mTestPlayerID 	= "";
	public int mCoin = 0;


	
	public void CreateRyu( string tTestPlayerID, string tGameServerURL )
	{
		mWWW = null;

		mTestPlayerID = tTestPlayerID;

		mGameServerURL = tGameServerURL;
	}
	public void DestroyRyu()
	{
	}



	public void SendReq( string tURL, MonoBehaviour tMono, RyuHandler tHandler )
	{
		//전송방식타입 설정
		mTypeTransmit = TYPE_GET;



		mpMone = tMono;
		SetHandler( tHandler );		
			
			
		string tServerURL = "";
		string tTotalURL = "";
		int ranInt = Random.Range(100000, 999999);	//인터넷 메커니즘의 특성 중 하나인 캐쉬 방지.


		mCurURL = tURL;
		
		
		tServerURL = mGameServerURL + "/";
		tTotalURL 	= tServerURL + tURL;	

		//코인에 대해서 요청을 특화시켰음. 
		//이 부분을 주석처리하고 tURL에 무엇을 담느냐에 따라 실제 동작을 다르게 할수도 있다.
		//그것은 (웹)서버프로그래머와 토의하여 결정하면 된다.
		tTotalURL = tTotalURL + "?id=" + mTestPlayerID + "&coin=" + mCoin.ToString() + "&" + ranInt
			+ "&seq=" + mSequenceIndex.ToString();
		

			Debug.Log ("tTotalURL: " + tTotalURL);

		//WWW객체 생성, 코루틴을 이용해 네트워크 수신을 대기
		mWWW = new WWW(  tTotalURL );		
		mpMone.StartCoroutine( OnReceiveXML() );			


		mSequenceIndex++;
	}
	
	IEnumerator OnReceiveXML() 
	{
		yield return mWWW;

		if( null == mWWW )
		{			
		}
		else
		{		
			XmlDocument tXML = null;
			tXML = new XmlDocument();
			
			if( null != tXML )
			{
				if( null != mWWW )
				{	
					Debug.Log ("receive WWW.text: " + mWWW.text);

					tXML.LoadXml( mWWW.text );				

					mHandler(tXML);

					//int tProtocolID = 0;
					//tProtocolID = Ryu._int( tNodeList.Item(0).InnerXml );
					//if( tProtocolID >= 0 ) //프로토콜이 유효한 것인지 판단한다.
					//{	
					//	mHandler(tXML);
					//}
				}
			}
		}
		
	}
	public void SetHandler( RyuHandler tHandler )
	{
		mHandler = tHandler;
	}

}
