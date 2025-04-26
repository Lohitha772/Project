import PyPDF2
import pyttsx3

def pdf_to_audio(pdf_path):
    try:
        # Open the PDF file
        with open(pdf_path, 'rb') as file:
            reader = PyPDF2.PdfReader(file)
            num_pages = len(reader.pages)
            
            # Initialize text-to-speech engine
            engine = pyttsx3.init()
            engine.setProperty('rate', 150)  # Adjust speech rate if needed
            
            # Loop through each page and read text
            for page_num in range(num_pages):
                page = reader.pages[page_num]
                text = page.extract_text()
                if text:
                    engine.say(text)
                else:
                    print(f"Warning: No text found on page {page_num + 1}")
            
            # Speak all the collected text
            engine.runAndWait()
    
    except FileNotFoundError:
        print(f"Error: File '{pdf_path}' not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    pdf_path = input("Enter the full path to the PDF file: ").strip()
    pdf_to_audio(pdf_path)
