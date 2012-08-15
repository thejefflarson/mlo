#ifndef MLO_STATUS_H
#define MLO_STATUS_H

namespace falconer {

class Status {
 public:
  Status() : code_(kOk) {};
  ~Status();

  static Status IoError() { return Status(IoError); }
  static Status Ok() { return Status(); }

  bool ok() { return code_ == kOk; }
  bool IsNotFound() { return code_ == kIoError; }

 private:
  void operator=(const Status&);
  Status(const Status&);

  enum Code {
    kOk,
    kIoError
  };

  Code code_;

  Status(Code code) : code_(code) {};
};

}

#endif
