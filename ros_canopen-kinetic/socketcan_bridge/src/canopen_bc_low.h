namespace CAN_keyboard
{
    class CANsend
    {
    public:
        CANsend(int ID, int time);
        int count;
        int que;
        int given_time;
    private:
        //void NMT(int given_time, char *mode, bool error); // Reset all networks
        void NMT();
        //void Int(int given_time, char *mode, bool error); // Initialize specific node.
        //void OP_mode(int ID, char* mode); // Enter to operation.
        //Target(char* mode);
        //Togo_abs(char* mode);
        //Togo_rel(char* mode);
    };
};