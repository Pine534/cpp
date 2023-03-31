#include <main.h>
#include <conn.h>

asio::io_context MainService;
static std::unique_ptr<boost::asio::io_context::work> MainWorkPtr;

int main() {
    MainWorkPtr = std::make_unique<boost::asio::io_context::work>(MainService);
    

    cout << "main start" << endl;
    conn::Init();
    cout << "init done" << endl;
    MainService.run();
}