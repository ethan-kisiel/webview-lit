#include <sqlite_orm/sqlite_orm.h>

#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

#include "webview.h"

// Define a simple database record
struct User {
  int id;
  std::string name;
  int visits;
};

inline auto create_storage(const std::string& filename) {
  using namespace sqlite_orm;
  return make_storage(
      filename, make_table("users", make_column("id", &User::id, primary_key()),
                           make_column("name", &User::name),
                           make_column("visits", &User::visits)));
}

void background_worker(webview::webview& w) {
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    w.eval(
        "window.dispatchEvent(new CustomEvent('myCustomEvent', {detail: { key: "
        "'value' }}));");
  }
}

int main() {
  // 1. Initialize SQLite storage
  auto storage = create_storage("app.db");
  storage.sync_schema();

  auto users_count = storage.count<User>();
  if (users_count == 0) {
    User user{1, "MacBook User", 1};
    storage.insert(user);
  } else {
    auto user = storage.get<User>(1);
    user.visits++;
    storage.update(user);
  }

  // 2. Locate frontend/dist/index.html relative to the executable or project
  // root Assuming you run the binary from the build/ directory, we navigate up
  // and into frontend/dist
  std::filesystem::path current_path = std::filesystem::current_path();
  std::filesystem::path html_path =
      current_path.parent_path() / "src" / "frontend" / "dist" / "index.html";

  std::string url = "file://" + html_path.string();

  // 3. Initialize and run the Webview window
  webview::webview w(false, nullptr);
  w.bind("getVisitorCount", [&](std::string seq) -> std::string {
    // Access your sqlite_orm database here
    auto user = storage.get<User>(1);

    // Return data back to JavaScript as a string or JSON
    return std::to_string(user.visits);
  });

  w.set_title("C++ Webview + SQLite + Lit Frontend");
  w.set_size(800, 600, WEBVIEW_HINT_NONE);
  w.navigate(url.c_str());
  std::thread t1(background_worker, std::ref(w));
  t1.detach();

  w.run();

  return 0;
}
