#include <iostream>

struct File;
struct Document;

// Wrong, complex interface
struct IMFMachine
{
   virtual void
   print(Document const& doc) = 0;
   virtual void
   scan(File const& srcFile, Document& doc) = 0;
   virtual void
   fax(Document const& doc) = 0;
};


// Better, segregated interfaces
struct IPrinter
{
   virtual void
   print(Document const& doc) = 0;
};

struct IScanner
{
   virtual void
   scan(File const& srcFile, Document& doc) = 0;
};

struct IFaxMachine
{
   virtual void
   fax(Document const& doc) = 0;
};

struct MFP : public IMFMachine
{
 public:
   void
   print(const Document& doc) override
   {
      // ok, it's a printer
   }

   void
   scan(const File& srcFile, Document& doc) override
   {
      // ok, it's a scanner
   }

   void
   fax(const Document& doc) override
   {
      // ok, it's a fax machine
   }
};

struct WickedScanner : public IMFMachine
{
 public:
   void
   print(const Document& doc) override
   {
      // not ok! it's not a printer
   }
   void
   scan(const File& srcFile, Document& doc) override
   {
      // ok, it's a scanner
   }
   void
   fax(const Document& doc) override
   {
      // not ok! it's not a fax machine
   }
};

struct NormalScanner : public IScanner
{
 public:
   void
   scan(const File& srcFile, Document& doc) override
   {
      // ok, it's just a scanner
   }
};

int
main()
{
}
