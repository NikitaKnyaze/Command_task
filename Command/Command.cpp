
#include <iostream>
#include <fstream>

class LogCommand {
public:
   virtual ~LogCommand() = default;
   virtual void print(const std::string& message) = 0;
};

class ConsoleMessage : public LogCommand
{
public:

   void print(const std::string& message) override
   {
      std::cout << message << std::endl;
   }
};

class FileMessage : public LogCommand
{
   std::ofstream file; 

public:
   FileMessage() {
      file.open("MessageFile.txt", std::ios::app); 

      if (!file) {
         throw std::runtime_error("Error opening file");
      }
   }

   void print(const std::string& message) override
   {
      if (file)
      {
         file << message << std::endl;
         std::cout << "File was open, and added text" << std::endl;
      }
      else
      {
         throw std::runtime_error("Error opening file");
      }
   }

   ~FileMessage() {
      if (file.is_open()) {
         file.close();
      }
   }
};

void print(LogCommand& comm)
{
   comm.print("SomeMessage");
}

int main()
{
   try
   {
      FileMessage mess;
      print(mess);
   }
   catch(const std::exception &e)
   {
      std::cout << e.what() << std::endl;
   }

   ConsoleMessage mess_1;
   print(mess_1);

   return 0;
}