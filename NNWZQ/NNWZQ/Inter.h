
typedef signed char TBOARD;

//以下函数在程序运行开始的时候调用，仅调用一次
extern "C" __declspec(dllexport) bool Login(char* strLoginName, char* strPassword);		//登录

extern "C" __declspec(dllexport) bool InitFromModelFile(char* strModelFileName);	//使用模型文件初始化
extern "C" __declspec(dllexport) bool InitWithoutModelFile(int nBoardWidth, int nBoardHeight, int nWinLen);		//无模型文件时初始化

//以下函数在每局游戏开始的时候调用，每局游戏调用一次
extern "C" __declspec(dllexport) bool StartNewGame();			//开始游戏，并重置相关数据

//以下函数在每步落子的时候调用，每步落子调用一次
extern "C" __declspec(dllexport) bool SetPieceWithCoord(int nX, int nY);	//根据坐标落子
extern "C" __declspec(dllexport) bool SetPieceWithGUI(CStatic* pCtrlBoard, int nCursorXInCtrl, int nCursorYInCtrl);		//根据界面组件及屏幕鼠标位置落子

extern "C" __declspec(dllexport) bool SetPieceByAI(void);					//AI落子，该函数返回失败表示所登录的用户积分不足
extern "C" __declspec(dllexport) bool SetPieceByAIAndShow(CStatic* pCtrlBoard);		//AI落子并在界面上显示

extern "C" __declspec(dllexport) bool IsGameOver();		//游戏是否已经结束
extern "C" __declspec(dllexport) int GetWinner();		//获胜者

extern "C" __declspec(dllexport) bool DrawBoard(CStatic* pCtrlBoard);		//绘制棋盘
extern "C" __declspec(dllexport) bool DrawPieces(CStatic* pCtrlBoard);		//绘制所有棋子

//以下函数在需要的时候调用，非必须调用
extern "C" __declspec(dllexport) TBOARD* GetBoardData(int* pnBoardWidth, int* pnBoardHeight);	//获得当前棋局数组的内存区首地址（及矩阵的宽和高，如果需要的话）
extern "C" __declspec(dllexport) int GetPoint();

extern "C" __declspec(dllexport) bool SaveSteps(char* strDataFileName);		//保存棋局数据
extern "C" __declspec(dllexport) bool SaveModel(char* strModelFileName);	//保存模型数据