#ifndef TEXTFORMATTING_HPP
#define TEXTFORMATTING_HPP
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>


namespace text_fmt {

class FormattedText
{
 public:
   std::string plain_text;
   std::vector< bool > caps;

   FormattedText(std::string text) : plain_text(std::move(text))
   {
      caps = std::vector< bool >(plain_text.length(), false);
   }

   void
   capitalize(std::size_t start, std::size_t end)
   {
      assert(start < end);
      assert(end < caps.size());

      for (size_t i = start; i <= end; ++i)
      {
         caps[i] = true;
      }
   }

   friend std::ostream&
   operator<<(std::ostream& os, const FormattedText& obj)
   {
      for (size_t i = 0; i < obj.plain_text.length(); ++i)
      {
         if (obj.caps[i])
         {
            os << (char)std::toupper(obj.plain_text[i]);
         }
         else
         {
            os << obj.plain_text[i];
         }
      }

      return os;
   }
};


class BetterFormattedText
{
 public:
   struct TextRange
   {
      size_t start, end;
      bool capitalize{false};
      bool bold{false};
      bool italic{false};

      bool
      covers(size_t position) const
      {
         return position >= start && position <= end;
      }
   };

   TextRange&
   getRange(size_t start, size_t end)
   {
      formatting.emplace_back(TextRange{start, end});

      return formatting.back();
   }

   BetterFormattedText(std::string text) : plain_text(std::move(text))
   {
   }

   friend std::ostream&
   operator<<(std::ostream& os, const BetterFormattedText& obj)
   {
      for (size_t i = 0; i < obj.plain_text.length(); ++i)
      {
         for (const auto& rng : obj.formatting)
         {
            auto c = obj.plain_text[i];
            if (rng.covers(i))
            {
               if (rng.capitalize)
               {
                  c = std::toupper(c);
               }
               //... etc.
            }
            os << (char)c;
         }
      }

      return os;
   }

 private:
   std::string plain_text;
   std::vector< TextRange > formatting;
};


} // namespace text_fmt

#endif // TEXTFORMATTING_HPP
